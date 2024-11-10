// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

// Sets default values
AGridManager::AGridManager()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	// 그리드 생성
	GenerateGrid();
	
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridManager::GenerateGrid()
{
    if (!ActorToSpawn) return;

    FVector StartLocation = GetActorLocation();

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Col = 0; Col < Columns; ++Col)
        {

            // 그리드 셀의 중심 위치 계산
            FVector SpawnLocation = StartLocation + FVector((Col + 0.5f) * CellSize, (Row + 0.5f) * CellSize, 0.0f);

            // 액터 스폰
            GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
        }
    }
}

