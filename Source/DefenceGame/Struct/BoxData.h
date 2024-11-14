// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BoxData.generated.h"

USTRUCT(BlueprintType)
struct FBoxData : public FTableRowBase
{

	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Box)
	float MaxHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Box)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Box)
	float Money;

};
