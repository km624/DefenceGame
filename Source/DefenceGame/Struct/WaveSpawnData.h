// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WaveSpawnData.generated.h"
 
USTRUCT(BlueprintType)
struct FWaveSpawnData : public FTableRowBase
 {

	 GENERATED_BODY()

 public:
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	 int32 Wave;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	 float SpawnTime;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	 int32 SpawnCount;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	 TMap<FName, float> BoxPercent;

	 


 };
