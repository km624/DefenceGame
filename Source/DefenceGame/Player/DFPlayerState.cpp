// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DFPlayerState.h"
#include "DefenceGame/DefenceGamePlayerController.h"

ADFPlayerState::ADFPlayerState()
{
	CurrentMoney = 0.0f;
	
}

void ADFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	SetDelegateToController();
	float StartMoney = 30.0f;
	SetMoney(StartMoney);
	
}

void ADFPlayerState::SetMoney(float newMoney)
{
	CurrentMoney += newMoney;
	
	UE_LOG(LogTemp, Warning, TEXT("CurrnetMoney: %f"), CurrentMoney);
	OnMoneyChanged.Broadcast(CurrentMoney);
}

void ADFPlayerState::SetDelegateToController()
{
	ADefenceGamePlayerController* playerController = Cast<ADefenceGamePlayerController>(GetPlayerController());
	playerController->SetMoneyWidget();
}


