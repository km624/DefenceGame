// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefenceGameCharacter.h"
#include "Struct/TowerData.h"
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
  float InitializeTower(class APlayerController* playerController, FTowerData newTowerData);


    void SetUpTower();

protected:

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	class USphereComponent* DetectionSphere;*/

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
    class UBoxComponent* DetectionBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float DetectDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float SpereSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
    int32 CurrentLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float AttackDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float AttackDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
    float TowerMoney;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
    float NextLevelTowerMoney;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
    FTowerData TowerData;

    FTimerHandle AttackTimerHandle;

    UPROPERTY()
    TObjectPtr<class APlayerController> PlayerController;

protected:
    void ShotSnowBall(class AActor* TargetActor);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
    TObjectPtr<class UAnimMontage> AttackAMotion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower)
    TSubclassOf<class ASnowBall> ProjectileClass;

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

public:
    UFUNCTION(BlueprintImplementableEvent, Category = TowerWidget, Meta = (DisplayName = "ShowOptionWidgetCpp"))
    void K2_OptionWidget();

    void OptionWidget();

    UFUNCTION(BlueprintCallable, Category = "UI", Meta = (DisplayName = "TowerRemoveCpp"))
    void TowerRemove();

    UFUNCTION(BlueprintCallable, Category = "UI", Meta = (DisplayName = "TowerLevelUpCpp"))
    bool TowerLevelUp(int32 Newlevel);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugBox")
    uint8 ShowDebug : 1;

   

};
