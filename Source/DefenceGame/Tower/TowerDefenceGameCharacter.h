// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefenceGameCharacter.h"
#include "TowerDefenceGameCharacter.generated.h"

/**
 * 
 */


UCLASS()
class DEFENCEGAME_API ATowerDefenceGameCharacter : public ADefenceGameCharacter
{
	GENERATED_BODY()
	

public:
    
    ATowerDefenceGameCharacter();

protected:
   
    virtual void BeginPlay() override;

public:
    
    virtual void Tick(float DeltaTime) override;


public:
   void SetUpTower(class APlayerController* playerController);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	class USphereComponent* DetectionSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float DetectDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float SpereSize;

    UPROPERTY()
    TObjectPtr<class APlayerController> PlayerController;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float AttackDelay;

    FTimerHandle AttackTimerHandle;

protected:
    void StartAttack();

protected:
    UPROPERTY()
    TArray<class AActor*> DetectBoxs;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    // 겹침 종료 시 호출되는 함수
    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
