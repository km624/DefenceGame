// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENCEGAME_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpawnComponent();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TObjectPtr<class AActor> StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TSubclassOf<class ACharacter> SpawnCharacter;


protected:
	void StartSpawn();



		
};
