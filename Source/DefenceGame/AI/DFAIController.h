// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DFAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ADFAIController : public AAIController
{
	GENERATED_BODY()



public:
	ADFAIController();

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Postion")
	TObjectPtr<class AActor> TargetPostion;
	
};
