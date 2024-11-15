// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DFPlayerState.h"

ADFPlayerState::ADFPlayerState()
{
	CurrentMoney = 30.0f;
}

void ADFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	
}

void ADFPlayerState::SetMoney(float newMoney)
{
	CurrentMoney += newMoney;
	
	if(CurrentMoney<0)
		UE_LOG(LogTemp, Warning, TEXT("Minus"), CurrentMoney);
	UE_LOG(LogTemp, Warning, TEXT("CurrnetMoney: %f"), CurrentMoney);
	OnMoneyChanged.Broadcast(CurrentMoney);
}
