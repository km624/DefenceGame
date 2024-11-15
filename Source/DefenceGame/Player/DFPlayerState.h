// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DFPlayerState.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoneyChangedDelegate, float /*CurrentMoney*/);

UCLASS()
class DEFENCEGAME_API ADFPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ADFPlayerState();

protected:
	virtual void BeginPlay() override;


public:
	FORCEINLINE float GetMoney() { return CurrentMoney; }
	
	FORCEINLINE void AddMoney(float newMoney) { CurrentMoney += newMoney; OnMonaeyChanged.Broadcast(CurrentMoney); }
	FORCEINLINE void MinusMoney(float newMoney) { CurrentMoney -= newMoney; OnMonaeyChanged.Broadcast(CurrentMoney); }

public:
	FOnMoneyChangedDelegate OnMonaeyChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Money")
	float CurrentMoney;
	
};
