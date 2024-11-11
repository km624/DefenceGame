// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
//#include "Components/StaticMeshComponent.h"

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
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Tower", Actors);
	AActor* DontSpawn;
	for (auto& Actor : Actors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s ,%s"), *Actor->GetActorNameOrLabel() ,*Actor->GetName());
		if (Actor->GetActorNameOrLabel() == TEXT("CubeGridToolOutput"))
		{
			DontSpawn = Actor;
			UE_LOG(LogTemp, Warning, TEXT("%s"),*DontSpawn->GetName());
		}
	}

	
    FVector StartLocation = GetActorLocation();

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Col = 0; Col < Columns; ++Col)
        {

            // 그리드 셀의 중심 위치 계산
            FVector SpawnLocation = StartLocation + FVector((Col + 0.5f) * CellSize, (Row + 0.5f) * CellSize, 0.0f);
			if (SpawnLocation == DontSpawn->GetActorLocation())
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap"));
			}
            // 액터 스폰
            GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
        }
    }
}

bool AGridManager::CheckIfSpawnLocationIsOccupied(const FVector& Location)
{
	// 겹치는 액터들을 저장할 배열
	TArray<AActor*> OverlappingActors;

	// 오버랩 체크
	bool bOverlap = GetWorld()->OverlapMultiByChannel(
		OverlappingActors,
		Location,
		FQuat::Identity,
		ECC_WorldStatic,
		FCollisionShape::MakeSphere(SpawnCheckSphere->GetScaledSphereRadius())
	);

	// 액터가 존재하면 true 반환
	return bOverlap && OverlappingActors.Num() > 0;
}

