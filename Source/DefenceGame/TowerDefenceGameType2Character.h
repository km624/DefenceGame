// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower/TowerDefenceGameCharacter.h"
#include "TowerDefenceGameType2Character.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ATowerDefenceGameType2Character : public ATowerDefenceGameCharacter
{
	GENERATED_BODY()

protected:
	virtual void StartAttack() override;

	
	virtual void TargetDestroy(AActor* destroyActor) override;

protected:
	bool bIsTargetDestroy;
	

	virtual float InitializeTower(class APlayerController* playerController, FTowerData newTowerData) override;
	

};
