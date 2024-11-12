// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DFAIController.h"
#include "Kismet/GameplayStatics.h"

ADFAIController::ADFAIController()
{
}

void ADFAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Position", Actors);
	
	for (auto& Actor : Actors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetActorNameOrLabel());
		if (Actor->GetActorNameOrLabel() ==TEXT("AITargetPostion"))
		{
			TargetPostion = Actor;
			break;
		}
	}

}

void ADFAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *InPawn->GetActorNameOrLabel());
	MoveToActor(TargetPostion, 5.0f, true, true, true, 0, true);
}
