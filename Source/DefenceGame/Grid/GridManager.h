// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class DEFENCEGAME_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGridManager();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

public:

	// 그리드 행과 열의 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Columns;

	// 각 그리드 셀의 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	// 스폰할 액터 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TSubclassOf<AActor> ActorToSpawn;

	// 그리드를 생성하는 함수
	void GenerateGrid();

	// 스폰 체크를 위한 구형 콜리전 컴포넌트
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	//class USphereComponent* SpawnCheckSphere;

	// 스폰 위치에 액터가 있는지 확인하는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	bool CheckIfSpawnLocationIsOccupied(const FVector& Location);

};
