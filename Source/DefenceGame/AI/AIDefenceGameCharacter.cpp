// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIDefenceGameCharacter.h"
#include "DFAIController.h"

AAIDefenceGameCharacter::AAIDefenceGameCharacter()
{
	static ConstructorHelpers::FClassFinder<ADFAIController>
		AICONTROLLER(TEXT("/Script/Engine.Blueprint'/Game/DefenceGame/Blueprint/BP_AIController.BP_AIController_C'"));
	if (AICONTROLLER.Class)
	{
		AIControllerClass = AICONTROLLER.Class;
	}
	
}
