// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DFPlayerState.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoneyChangedDelegate, float /*CurrentMoney*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLifeChangedDelegate, int32 /*CDurrentLife*/);

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
	FORCEINLINE int32 GetCurrentLife() { return CurrentLife; }
	
	void SetMoney(float newMoney);

	void SetCurrentLife(int32 newLife);

	void GameOver();

public:
	FOnMoneyChangedDelegate OnMoneyChanged;
	FOnLifeChangedDelegate	OnLifeChanged;
private:

	void SetDelegateToController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Money")
	float CurrentMoney;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life")
	int32 CurrentLife;


	
};
