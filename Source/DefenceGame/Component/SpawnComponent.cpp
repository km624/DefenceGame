// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpawnComponent.h"
#include "AI/AIDefenceGameCharacter.h"
#include "AI/DFAIController.h"
#include "Engine/World.h"
#include "DefenceGame/DefenceGamePlayerController.h"
#include "Player/DFPlayerState.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;

	FString contextString;
	TArray<FWaveSpawnData*> RowArray;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAVE(TEXT("/Script/Engine.DataTable'/Game/DefenceGame/Data/DT_SpawnWave.DT_SpawnWave'"));
	if (DT_WAVE.Object)
	{
		SpawnDataTable = DT_WAVE.Object;
	}
	if (IsValid(SpawnDataTable))
	{
		SpawnDataTable->GetAllRows<FWaveSpawnData>(contextString, RowArray);
		for (FWaveSpawnData* Row : RowArray)
		{
			if (Row)
			{
				
				DataArray.Add(*Row);
			}
		}
	}

	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOX(TEXT("/Script/Engine.DataTable'/Game/DefenceGame/Data/DT_BoxData.DT_BoxData'"));
	if (DT_BOX.Object)
	{
		BoxSpawnDataTable = DT_BOX.Object;
	}
	TArray<FName> rowNames = BoxSpawnDataTable->GetRowNames();
	FString contextString2;
	for (FName rowName : rowNames)
	{
		const FBoxData* rowInfo = BoxSpawnDataTable->FindRow<FBoxData>(rowName, contextString2);
		BoxDataMap.Add(rowName, *rowInfo);
	}
	

	CurrentWave = 1;

}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDelegateToController();

	SetSpawnWave(CurrentWave);
	//SpawnWaveDelay(CurrentWave);

	//BoxSpawn();
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


void USpawnComponent::SetDelegateToController()
{
	ADefenceGamePlayerController* playerController = Cast<ADefenceGamePlayerController>(GetWorld()->GetFirstPlayerController());
	if (playerController)
	{
		OnWaveChanged.AddUObject(playerController, &ADefenceGamePlayerController::OnWaveChanged);
		playerController->SetSpawnComponent(this);
	}
}

//void USpawnComponent::SpawnWaveDelay(int32 Wave)
//{
//	if (bIsGameover)return;
//	UE_LOG(LogTemp, Warning, TEXT("DelayStrat"));
//	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, [this, Wave]()
//		{
//			//BoxSpawn();
//			SetSpawnWave(Wave);
//		}, 3.0f, false);
//
//	
//}
//
//void USpawnComponent::SetSpawnWave(int32 Wave)
//{
//	if (DataArray.Num() > 0)
//	{
//		CurrentWave = DataArray[Wave - 1].Wave;
//
//		BoxCount = DataArray[Wave - 1].SpawnCount;
//
//		SpawnTime = DataArray[Wave - 1].SpawnTime;
//	}
//	else
//		UE_LOG(LogTemp, Warning, TEXT("Array Empty"));
//
//	UE_LOG(LogTemp, Warning, TEXT("%d Wave Start"), CurrentWave);
//
//	OnWaveChanged.Broadcast(CurrentWave);
//	BoxSpawn();
//	//GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &ThisClass::BoxSpawn, false);
//
//	
//}

void USpawnComponent::SpawnWaveDelay(int32 Wave)
{
	UE_LOG(LogTemp, Warning, TEXT("DelayStrat"));
	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, [this]()
		{
			SantaSpawn();
			SetTimer();
		}, 3.0f, false);
}

void USpawnComponent::SetSpawnWave(int32 Wave)
{
	if (DataArray.Num() > 0)
	{
		CurrentWave = DataArray[Wave - 1].Wave;

		BoxCount = DataArray[Wave - 1].SpawnCount;

		SpawnTime = DataArray[Wave - 1].SpawnTime;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Array Empty"));

	UE_LOG(LogTemp, Warning, TEXT("%d Wave Start"), CurrentWave);

	if (bIsGameover)return;
	OnWaveChanged.Broadcast(CurrentWave);
	SpawnWaveDelay(CurrentWave);
}

void USpawnComponent::BoxSpawn()
{
	if (SpawnCharacter && StartPosition)
	{
		const FTransform SpawnTransform(StartPosition->GetActorLocation());
		FBoxData boxdData = BoxDataMap["Normal"];
		AAIDefenceGameCharacter* aiCharacter = GetWorld()->SpawnActorDeferred<AAIDefenceGameCharacter>(SpawnCharacter, SpawnTransform);
		if (aiCharacter)
		{
			aiCharacter->SetUpBox(boxdData);
			aiCharacter->OnDestroyed.AddDynamic(this, &USpawnComponent::BoxOnDead);
			
			CurrentSpawnBox.Add(aiCharacter);

			aiCharacter->FinishSpawning(SpawnTransform);
		}

		ADFAIController* aiController = GetWorld()->SpawnActor<ADFAIController>(ADFAIController::StaticClass(), StartPosition->GetActorLocation(), FRotator::ZeroRotator);
		aiController->Possess(aiCharacter);
	}
	
	BoxCount--;
	if (BoxCount > 0)
		SetTimer();


}

void USpawnComponent::SantaSpawn()
{
	if (SpawnSanta && StartPosition)
	{
		const FTransform SpawnTransform(StartPosition->GetActorLocation());
		FBoxData boxdData = BoxDataMap["Normal"];
		AAIDefenceGameCharacter* aiCharacter = GetWorld()->SpawnActorDeferred<AAIDefenceGameCharacter>(SpawnSanta, SpawnTransform);
		if (aiCharacter)
		{
			aiCharacter->SetUpBox(boxdData);
			aiCharacter->OnDestroyed.AddDynamic(this, &USpawnComponent::BoxOnDead);

			CurrentSpawnBox.Add(aiCharacter);

			aiCharacter->FinishSpawning(SpawnTransform);
		}

		ADFAIController* aiController = GetWorld()->SpawnActor<ADFAIController>(ADFAIController::StaticClass(), StartPosition->GetActorLocation(), FRotator::ZeroRotator);
		aiController->Possess(aiCharacter);
	}
}

void USpawnComponent::NextWave()
{
	CurrentWave++;
	//SpawnWaveDelay(CurrentWave);
	SetSpawnWave(CurrentWave);
	
}




void USpawnComponent::SetTimer()
{

	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &USpawnComponent::BoxSpawn, SpawnTime);
	
}

void USpawnComponent::BoxOnDead(AActor* deadBox)
{
	
	
	AAIDefenceGameCharacter* DeadBox = Cast<AAIDefenceGameCharacter>(deadBox);
	CurrentSpawnBox.Remove(DeadBox);
	

	if (CurrentSpawnBox.Num() <= 0)
	{
		NextWave();
	}
	
}

void USpawnComponent::AllTimeHandleStop()
{
	bIsGameover = true;
	SpawnTimeHandle.Invalidate();
	WaveTimerHandle.Invalidate();
	UE_LOG(LogTemp, Warning, TEXT("Handle Stop"));
}

