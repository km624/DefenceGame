// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefenceGamePlayerController.h"
//#include "GameFramework/Pawn.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "DefenceGameCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
//#include "Engine/LocalPlayer.h"
#include "Grid/GridManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Tower/TowerDefenceGameCharacter.h"
#include "Player/DFPlayerState.h"
#include "Blueprint/UserWidget.h"



DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADefenceGamePlayerController::ADefenceGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	//타워 데이타
	FString contextString;
	TArray<FTowerData*> RowArray;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Tower(TEXT("/Script/Engine.DataTable'/Game/DefenceGame/Data/DT_TowerData.DT_TowerData'"));
	if (DT_Tower.Object)
	{
		TowerDataTable = DT_Tower.Object;
	}
	if (IsValid(TowerDataTable))
	{
		TowerDataTable->GetAllRows<FTowerData>(contextString, RowArray);
		for (FTowerData* Row : RowArray)
		{
			if (Row)
			{

				DataArray.Add(*Row);
			}
		}
	}

	//HUD
	static ConstructorHelpers::FClassFinder<UUserWidget>WIDGET_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DefenceGame/Blueprint/UI/BP_Hud.BP_Hud_C'"));
	if (WIDGET_HUD.Class) 
		HUDWidgetClass = WIDGET_HUD.Class;
}

void ADefenceGamePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FInputModeGameAndUI GameAndUI;
	SetInputMode(GameAndUI);

	SetUpGridManager();

	SetUpCamera();

	//SetUpPreview();
	
}

void ADefenceGamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bSelectTower)
		UpdatePreview();
}

void ADefenceGamePlayerController::SetUpGridManager()
{
	// 그리드 매니저 찾기
	for (TActorIterator<AGridManager> It(GetWorld()); It; ++It)
	{
		GridManager = *It;
		break;
	}
}

void ADefenceGamePlayerController::SetUpCamera()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MainCamera", Actors);
	if (Actors.Num())
	{
		MainCamera = Actors[0];
		SetViewTarget(MainCamera);
	}
}


void ADefenceGamePlayerController::SetUpPreview(TSubclassOf<class ATowerDefenceGameCharacter> TowerDefenceCharacterClass)
{
	PreviewActorClass = TowerDefenceCharacterClass;
	if (PreviewActorClass)
	{
		//PreviewActor = GetWorld()->SpawnActor<ATowerDefenceGameCharacter>(PreviewActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
		ADFPlayerState* playerState = Cast<ADFPlayerState>(PlayerState);
		PreviewActor = GetWorld()->SpawnActorDeferred<ATowerDefenceGameCharacter>(PreviewActorClass, FTransform());
		
		if (PreviewActor)
		{
			PreviewTowerMoney = PreviewActor->InitializeTower(this, DataArray[0]);
			
			if (PreviewTowerMoney > playerState->GetMoney())
			{
				bSelectTower = false;
				PreviewActorClass = NULL;
				PreviewActor->Destroy();
				UE_LOG(LogTemp, Warning, TEXT("NoMoney"));
				return;
			}

			PreviewActor->SetActorHiddenInGame(true);
			PreviewActor->FinishSpawning(FTransform());
		
		}

	}
}


void ADefenceGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//// Setup mouse input events

		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefenceGamePlayerController::ClickMouseLeft);
		
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADefenceGamePlayerController::OnSetDestinationTriggered);
		
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADefenceGamePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetTowerRotaionAction, ETriggerEvent::Started, this, &ADefenceGamePlayerController::SetTowerRotaion);
		EnhancedInputComponent->BindAction(IACameraMove, ETriggerEvent::Triggered, this, &ADefenceGamePlayerController::SetCameraMove);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}



void ADefenceGamePlayerController::UpdatePreview()
{
	if (!GridManager || !PreviewActor) return;

	// 마우스 히트 결과 얻기
	FHitResult HitResult;

	
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		
		if (HitResult.GetActor()->ActorHasTag(TEXT("TowerSpawn")))
		{
			
			 //셀 중심 위치 계산
			CanSpawnLocation = HitResult.GetActor()->GetActorLocation()+FVector(0.0f,0.0f,90.0f);
			bIsCanSpawn = true;
			PreviewActor->SetActorLocation(CanSpawnLocation);
			PreviewActor->SetActorHiddenInGame(false);
		}
		else
		{
			bIsCanSpawn = false;
			PreviewActor->SetActorHiddenInGame(true);
		}
		
		//FVector HitLocation = HitResult.Location;
		//
		//// 그리드 매니저 위치 기준으로 상대 위치 계산
		//FVector GridOrigin = GridManager->GetActorLocation();
		//FVector RelativeLocation = HitLocation - GridOrigin;
		//
		//// 그리드 셀 인덱스 계산
		//int32 Col = FMath::FloorToInt(RelativeLocation.X / GridManager->CellSize);
		//int32 Row = FMath::FloorToInt(RelativeLocation.Y / GridManager->CellSize);

		////UE_LOG(LogTemp, Warning, TEXT("Col : %d , Row : %d"), Col, Row);

		//// 유효한 인덱스인지 확인
		//if (Col >= 0 && Col < GridManager->Columns && Row >= 0 && Row < GridManager->Rows)
		//{
		//	if (HitResult.GetActor()->ActorHasTag(TEXT("TowerSpawn")))
		//	{
		//		// 셀 중심 위치 계산
		//		FVector CellCenter = GridOrigin + FVector((Col + 0.5f) * GridManager->CellSize, (Row + 0.5f) * GridManager->CellSize, 190.0f);
		//		CanSpawnLocation = CellCenter;
		//		bIsCanSpawn = true;
		//		PreviewActor->SetActorLocation(CellCenter);
		//		PreviewActor->SetActorHiddenInGame(false);
		//	}
		//}
		//else
		//{
		//	bIsCanSpawn = false;
		//	PreviewActor->SetActorHiddenInGame(true);
		//}
	}
	else
	{
		bIsCanSpawn = false;
		PreviewActor->SetActorHiddenInGame(true);
	}
}

void ADefenceGamePlayerController::ClickMouseLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("Click"));
	if (bSelectTower)
	{
		SpawnTower();
	}
		
	else
	{
		ShowTowerOption();
	}
		
	
		
}

void ADefenceGamePlayerController::SpawnTower()
{
	if (bIsCanSpawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("SetTower"));
		FHitResult Hit;
		bool bHitSuccessful = false;
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		if (Hit.GetActor()->ActorHasTag(TEXT("TowerSpawn")))
		{
			ADFPlayerState* playerState = Cast<ADFPlayerState>(PlayerState);
			
				const FTransform SpawnTransform(PreviewActor->GetActorRotation(), CanSpawnLocation);
				ATowerDefenceGameCharacter* SpawnedActor = GetWorld()->SpawnActorDeferred<ATowerDefenceGameCharacter>(PreviewActorClass, SpawnTransform);

				if (SpawnedActor)
				{
					playerState->SetMoney(-(SpawnedActor->InitializeTower(this, DataArray[0])));
					SpawnedActor->SetUpTower();
					Hit.GetActor()->Destroy();
					bIsCanSpawn = false;
					SpawnedActor->FinishSpawning(SpawnTransform);

					
					bSelectTower = false;
					PreviewActorClass = NULL;
					PreviewActor->Destroy();
				}
		}
	}
	
}

void ADefenceGamePlayerController::ShowTowerOption()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	if (Hit.GetActor()->ActorHasTag(TEXT("Tower")))
	{
		ATowerDefenceGameCharacter* select = Cast<ATowerDefenceGameCharacter>(Hit.GetActor());
		if (SelectTower)
		{
			SelectTower->OptionWidget();
			if (SelectTower == select)
			{
				SelectTower = NULL;
			}
			else
			{
				SelectTower = select;
				SelectTower->OptionWidget();
			}
		}
		else
		{
			SelectTower = select;
			SelectTower->OptionWidget();
		}
	}
	else
	{
		if (SelectTower)
		{
			SelectTower->OptionWidget();
			SelectTower = NULL;
		}
		
	}
	
}

void ADefenceGamePlayerController::SetTowerRotaion(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	PreviewActor->SetActorRotation(FRotator(0.0f,PreviewActor->GetActorRotation().Yaw + 90.0f*MovementVector.X ,0.0f));
	
	
}

void ADefenceGamePlayerController::SetCameraMove(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();

	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);

	MainCamera->AddActorLocalOffset(MoveDirection * CameraSpeed, true);
}

void ADefenceGamePlayerController::OnMoneyChanged(float newMoney)
{
	K2_OnMoneyChanged(newMoney);
	
}

void ADefenceGamePlayerController::OnWaveChanged(int32 newWave)
{
	K2_OnWaveChanged(newWave);
	//UE_LOG(LogTemp, Warning, TEXT("WaveChange"));
}

void ADefenceGamePlayerController::NoMoneyAlert()
{
	K2_NoMoneyAlert();
}

void ADefenceGamePlayerController::SetMoneyWidget()
{

	ADFPlayerState* playerState = Cast<ADFPlayerState>(PlayerState);
	playerState->OnMoneyChanged.AddUObject(this, &ThisClass::OnMoneyChanged);

}



