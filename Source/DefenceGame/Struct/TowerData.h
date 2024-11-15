// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TowerData.generated.h"

USTRUCT(BlueprintType)
struct FTowerData : public FTableRowBase
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =Tower)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
	float AttackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
	float AttackDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
	float TowerMoney;

};