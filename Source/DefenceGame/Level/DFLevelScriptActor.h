// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DFLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ADFLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ADFLevelScriptActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TObjectPtr<class USpawnComponent> SpawnComponent;



	
};
