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
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "TargetPosition", Actors);
	if(Actors.Num())
		TargetPostion = Actors[0];

	MoveToActor(TargetPostion, 5.0f, true, true, true, 0, true);
	
}
