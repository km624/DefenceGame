// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Engine/OverlapResult.h"
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

    FVector StartLocation = GetActorLocation();

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Col = 0; Col < Columns; ++Col)
        {
            // �׸��� ���� �߽� ��ġ ���
            FVector SpawnLocation = StartLocation + FVector((Col + 0.5f) * CellSize, (Row + 0.5f) * CellSize, 100.0f);
            if (CheckIfSpawnLocationIsOccupied(SpawnLocation))
            {
                // ���� ����
                GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
            }
        
        }
    }
}

bool AGridManager::CheckIfSpawnLocationIsOccupied(const FVector& Location)
{
    // �������� ���͵��� ������ �迭
    TArray<FOverlapResult> OverlapResults;

    // �浹 ����: �������� ���� �浹 ä�� �� �Ķ���� ����
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // ���� ���ʹ� �˻翡�� ����

    // �������� ���� ���� (�� ����)
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0f);

    // ���忡�� ������ �˻� ����
    bool bHasOverlap = GetWorld()->OverlapMultiByChannel(
        OverlapResults,              // ������ ����� ������ �迭
        Location,              // �˻��� ��ġ
        FQuat::Identity,            // ȸ�� ����
        ECC_WorldDynamic,           // �浹 ä�� ���� (�ʿ信 ���� ���� ����)
        CollisionShape,             // ������ ����
        QueryParams                 // �浹 ���� �Ķ����
    );

    if (bHasOverlap)
    {
        // �������� ��� �� "Tower" �±׸� ���� ���Ͱ� �ִ��� Ȯ��
        for (const FOverlapResult& Result : OverlapResults)
        {
            AActor* OverlappedActor = Result.GetActor();
            if (OverlappedActor && OverlappedActor->ActorHasTag("TowerPosition"))
            {
                
                // "Tower" �±׸� ���� ���Ͱ� ������
                return true;
            }
        }
    }
    // "Tower" �±׸� ���� ���Ͱ� �������� ����
    return false;
}

