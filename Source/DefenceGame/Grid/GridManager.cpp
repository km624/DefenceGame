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
            FVector SpawnLocation = StartLocation + FVector((Col + 0.5f) * CellSize, (Row + 0.5f) * CellSize, 100.0f);
            if (CheckIfSpawnLocationIsOccupied(SpawnLocation))
            {
                // 액터 스폰
                GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
            }
        
        }
    }
}

bool AGridManager::CheckIfSpawnLocationIsOccupied(const FVector& Location)
{
    // 오버랩된 액터들을 저장할 배열
    TArray<FOverlapResult> OverlapResults;

    // 충돌 설정: 오버랩을 위한 충돌 채널 및 파라미터 설정
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // 현재 액터는 검사에서 제외

    // 오버랩할 도형 설정 (구 형태)
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0f);

    // 월드에서 오버랩 검사 수행
    bool bHasOverlap = GetWorld()->OverlapMultiByChannel(
        OverlapResults,              // 오버랩 결과를 저장할 배열
        Location,              // 검사할 위치
        FQuat::Identity,            // 회전 없음
        ECC_WorldDynamic,           // 충돌 채널 설정 (필요에 따라 변경 가능)
        CollisionShape,             // 오버랩 도형
        QueryParams                 // 충돌 쿼리 파라미터
    );

    if (bHasOverlap)
    {
        // 오버랩된 결과 중 "Tower" 태그를 가진 액터가 있는지 확인
        for (const FOverlapResult& Result : OverlapResults)
        {
            AActor* OverlappedActor = Result.GetActor();
            if (OverlappedActor && OverlappedActor->ActorHasTag("TowerPosition"))
            {
                
                // "Tower" 태그를 가진 액터가 존재함
                return true;
            }
        }
    }
    // "Tower" 태그를 가진 액터가 존재하지 않음
    return false;
}

