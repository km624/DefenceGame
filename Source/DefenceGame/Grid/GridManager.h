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

	// �׸��� ��� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Columns;

	// �� �׸��� ���� ũ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	// ������ ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TSubclassOf<AActor> ActorToSpawn;

	// �׸��带 �����ϴ� �Լ�
	void GenerateGrid();

};
