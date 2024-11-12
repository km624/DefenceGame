// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/DFLevelScriptActor.h"
#include "Component/SpawnComponent.h"

ADFLevelScriptActor::ADFLevelScriptActor()
{
	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn"));
}
