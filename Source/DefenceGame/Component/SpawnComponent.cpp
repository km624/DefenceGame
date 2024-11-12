// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpawnComponent.h"
#include "AI/AIDefenceGameCharacter.h"
#include "AI/DFAIController.h"
#include "Level/DFLevelScriptActor.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	
	//PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	StartSpawn();
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void USpawnComponent::StartSpawn()
{
	
	if (SpawnCharacter && StartPosition)
	{

		GetWorld()->SpawnActor<AActor>(SpawnCharacter, StartPosition->GetActorLocation(), FRotator::ZeroRotator);
	}

		

}

