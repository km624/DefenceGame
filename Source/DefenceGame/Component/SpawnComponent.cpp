// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpawnComponent.h"
#include "AI/AIDefenceGameCharacter.h"
#include "AI/DFAIController.h"
#include "Level/DFLevelScriptActor.h"

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
	CurrentWave = 1;

}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	SetSpawnWave(CurrentWave);
	BoxSpawn();
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
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
	
}

void USpawnComponent::BoxSpawn()
{
	if (SpawnCharacter && StartPosition)
	{
		
		AAIDefenceGameCharacter* aiCharacter = GetWorld()->SpawnActor<AAIDefenceGameCharacter>(SpawnCharacter, StartPosition->GetActorLocation(), FRotator::ZeroRotator);
		ADFAIController* aiController = GetWorld()->SpawnActor<ADFAIController>(ADFAIController::StaticClass(), StartPosition->GetActorLocation(), FRotator::ZeroRotator);
		aiController->Possess(aiCharacter);
	}

	BoxCount--;
	if (BoxCount > 0)
		SetTimer();
	else
	{
		CurrentWave++;
		SetSpawnWave(CurrentWave);
		BoxSpawn();
	}

}

void USpawnComponent::SetTimer()
{

	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &USpawnComponent::BoxSpawn, SpawnTime);
	
}

