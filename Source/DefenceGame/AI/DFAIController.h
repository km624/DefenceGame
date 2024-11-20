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

	virtual void OnPossess(APawn* InPawn) override;

	void MoveBoxToLocation(int32 pos);

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Postion")
	TArray<FVector> TargetPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Postion")
	int32 CurrentTargetPos;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Postion")
	TObjectPtr<class AActor> TargetPostion;


	
};
