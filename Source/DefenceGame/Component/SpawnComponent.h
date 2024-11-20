// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Struct/WaveSpawnData.h"
#include "Struct/BoxData.h"
#include "SpawnComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWaveChangedDelegate, int32 /*CurrentWave*/);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TSubclassOf<class ACharacter> SpawnSanta;


protected:
	void SetDelegateToController();

	void SpawnWaveDelay(int32 Wave);

	void SetSpawnWave(int32 Wave);

	FName SelectBox();

	void BoxSpawn();

	void SantaSpawn();

	UFUNCTION()
	void NextWave();
	
	void SetTimer();

protected:
	UFUNCTION()
	void BoxOnDead(AActor* deadBox);


public:
	FOnWaveChangedDelegate OnWaveChanged;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnData)
	UDataTable* SpawnDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<FWaveSpawnData> DataArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	int32 CurrentWave;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	int32 BoxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float SpawnTime;

public:
	
	FTimerHandle SpawnTimeHandle;

	
	FTimerHandle WaveTimerHandle;

protected:

	TArray <class AAIDefenceGameCharacter*> CurrentSpawnBox;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnBoxData)
	UDataTable* BoxSpawnDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BoxData)
	TMap<FName , FBoxData> BoxDataMap;


public:
	void AllTimeHandleStop();

protected:
	uint8 bIsGameover : 1;
		
};
