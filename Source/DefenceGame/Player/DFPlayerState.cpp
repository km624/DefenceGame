// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DFPlayerState.h"
#include "DefenceGame/DefenceGamePlayerController.h"

ADFPlayerState::ADFPlayerState()
{
	CurrentMoney = 0.0f;
	CurrentLife = 3;
	
}

void ADFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	SetDelegateToController();
	float StartMoney = 50.0f;
	SetMoney(StartMoney);
	
}

void ADFPlayerState::SetMoney(float newMoney)
{
	CurrentMoney += newMoney;
	
	//UE_LOG(LogTemp, Warning, TEXT("CurrnetMoney: %f"), CurrentMoney);
	OnMoneyChanged.Broadcast(CurrentMoney);
}

void ADFPlayerState::SetCurrentLife(int32 newLife)
{
	CurrentLife -= newLife;
	
	OnLifeChanged.Broadcast(CurrentLife);
	

	if (CurrentLife == 0)
	{
		GameOver();
	}
	
}

void ADFPlayerState::GameOver()
{
	ADefenceGamePlayerController* playerController = Cast<ADefenceGamePlayerController>(GetPlayerController());
	playerController->GameOver();
}

void ADFPlayerState::SetDelegateToController()
{
	ADefenceGamePlayerController* playerController = Cast<ADefenceGamePlayerController>(GetPlayerController());
	playerController->SetMoneyWidget();
	playerController->SetLifeWidget();
}


