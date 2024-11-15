// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefenceGameGameMode.h"
#include "DefenceGamePlayerController.h"
#include "DefenceGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/DFPlayerState.h"


ADefenceGameGameMode::ADefenceGameGameMode()
{

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Script/Engine.Blueprint'/Game/DefenceGame/Blueprint/BP_TopDownPlayerController.BP_TopDownPlayerController'"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass =  ADFPlayerState::StaticClass();
	
}