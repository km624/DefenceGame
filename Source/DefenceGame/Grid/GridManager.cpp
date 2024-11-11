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

	// �׸��� ����
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

            // �׸��� ���� �߽� ��ġ ���
            FVector SpawnLocation = StartLocation + FVector((Col + 0.5f) * CellSize, (Row + 0.5f) * CellSize, 0.0f);
			if (SpawnLocation == DontSpawn->GetActorLocation())
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap"));
			}
            // ���� ����
            GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
        }
    }
}

bool AGridManager::CheckIfSpawnLocationIsOccupied(const FVector& Location)
{
	// ��ġ�� ���͵��� ������ �迭
	TArray<AActor*> OverlappingActors;

	// ������ üũ
	bool bOverlap = GetWorld()->OverlapMultiByChannel(
		OverlappingActors,
		Location,
		FQuat::Identity,
		ECC_WorldStatic,
		FCollisionShape::MakeSphere(SpawnCheckSphere->GetScaledSphereRadius())
	);

	// ���Ͱ� �����ϸ� true ��ȯ
	return bOverlap && OverlappingActors.Num() > 0;
}

