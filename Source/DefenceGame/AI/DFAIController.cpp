// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DFAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DefenceGame/DefenceGamePlayerController.h"
#include "Player/DFPlayerState.h"

ADFAIController::ADFAIController()
{
}

void ADFAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Position", Actors);
	
	FString BaseString = TEXT("AITargetPostion");
	for (int j=1;j<Actors.Num()+1;j++)
	{
	
		FString NewString = BaseString + FString::FromInt(j);
		for (int i = 0; i < Actors.Num() ; i++)
		{
			if (Actors[i]->GetActorNameOrLabel() == NewString)
			{
				TargetPositions.Add(Actors[i]->GetActorLocation());

				//UE_LOG(LogTemp, Warning, TEXT("%s"),*NewString);
			}
		}

	}
	CurrentTargetPos = 1;

}

void ADFAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *InPawn->GetActorNameOrLabel());
	//MoveToActor(TargetPostion, 5.0f, true, true, true, 0, true);
	
	MoveBoxToLocation(CurrentTargetPos);
	
}

void ADFAIController::MoveBoxToLocation(int32 pos)
{
	MoveToLocation(TargetPositions[pos - 1]);
	
}

void ADFAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
	if (Result.IsSuccess())
	{
		if (GetPawn())
		{
			if (CurrentTargetPos != TargetPositions.Num())
			{
				CurrentTargetPos++;
				MoveBoxToLocation(CurrentTargetPos);
			}
			else
			{
				if (GetPawn()->ActorHasTag("Box"))
				{
					ADefenceGamePlayerController* playerController = Cast<ADefenceGamePlayerController>(GetWorld()->GetFirstPlayerController());
					ADFPlayerState* playerState = Cast<ADFPlayerState>(playerController->PlayerState);
					playerState->SetCurrentLife(1);
				}
				GetPawn()->Destroy();

			}

		}
	}
	
}

