// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpawnComponent.h"
#include "AI/AIDefenceGameCharacter.h"
#include "AI/DFAIController.h"
#include "Level/DFLevelScriptActor.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	
	//PrimaryComponentTick.bCanEverTick = true;
	BoxCount = 5;
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	BoxSpawn();
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void USpawnComponent::BoxSpawn()
{
	if (SpawnCharacter && StartPosition)
	{
		
		AAIDefenceGameCharacter* aiCharacter = GetWorld()->SpawnActor<AAIDefenceGameCharacter>(SpawnCharacter, StartPosition->GetActorLocation(), FRotator::ZeroRotator);
		ADFAIController* aiController = GetWorld()->SpawnActor<ADFAIController>(ADFAIController::StaticClass(), StartPosition->GetActorLocation(), FRotator::ZeroRotator);
		aiController->Possess(aiCharacter);
	}

	BoxCount-=1;
	if (BoxCount > 0)
		SetTimer();

}

void USpawnComponent::SetTimer()
{

	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &USpawnComponent::BoxSpawn, SpawnDelay);
	
}

