// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefenceGamePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "DefenceGameCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Grid/GridManager.h"
#include "EngineUtils.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADefenceGamePlayerController::ADefenceGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ADefenceGamePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// 그리드 매니저 찾기


	for (TActorIterator<AGridManager> It(GetWorld()); It; ++It)
	{
		GridManager = *It;
		break;
	}
	if (PreviewActorClass)
	{
		PreviewActor = GetWorld()->SpawnActor<AActor>(PreviewActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (PreviewActor)
		{
			PreviewActor->SetActorHiddenInGame(true);
		}

	}
}

void ADefenceGamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdatePreview();
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
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefenceGamePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADefenceGamePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADefenceGamePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADefenceGamePlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ADefenceGamePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ADefenceGamePlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ADefenceGamePlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ADefenceGamePlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADefenceGamePlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ADefenceGamePlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ADefenceGamePlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ADefenceGamePlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ADefenceGamePlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ADefenceGamePlayerController::UpdatePreview()
{
	if (!GridManager || !PreviewActor) return;

	// 마우스 히트 결과 얻기
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		FVector HitLocation = HitResult.Location;

		// 그리드 매니저 위치 기준으로 상대 위치 계산
		FVector GridOrigin = GridManager->GetActorLocation();
		FVector RelativeLocation = HitLocation - GridOrigin;

		// 그리드 셀 인덱스 계산
		int32 Col = FMath::FloorToInt(RelativeLocation.X / GridManager->CellSize);
		int32 Row = FMath::FloorToInt(RelativeLocation.Y / GridManager->CellSize);

		// 유효한 인덱스인지 확인
		if (Col >= 0 && Col < GridManager->Columns && Row >= 0 && Row < GridManager->Rows)
		{
			// 셀 중심 위치 계산
			FVector CellCenter = GridOrigin + FVector((Col + 0.5f) * GridManager->CellSize, (Row + 0.5f) * GridManager->CellSize, 0.0f);
			
			PreviewActor->SetActorLocation(CellCenter);
			PreviewActor->SetActorHiddenInGame(false);
		}
		else
		{
			PreviewActor->SetActorHiddenInGame(true);
		}
	}
	else
	{
		PreviewActor->SetActorHiddenInGame(true);
	}
}
