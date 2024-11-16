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
	
	
	void SetMoney(float newMoney);

public:
	FOnMoneyChangedDelegate OnMoneyChanged;

private:

	void SetDelegateToController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Money")
	float CurrentMoney;


	
};
