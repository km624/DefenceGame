// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameType2Character.h"
#include "Kismet/GameplayStatics.h"

void ATowerDefenceGameType2Character::StartAttack()
{
    if (DetectBoxs.Num() > 0)
    {

        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        AnimInstance->Montage_Play(AttackAMotion, 1.3f);

        UGameplayStatics::PlaySoundAtLocation(this, ThrowSound, GetActorLocation());
        int32 CurrentDetectBoxs = FMath::Clamp(DetectBoxs.Num(), 1, 3);
        for (int32 i = 0; i < CurrentDetectBoxs; i++)
        {
                ShotSnowBall(DetectBoxs[i]);
                //DetectBoxs[i]->OnDestroyed.AddDynamic(this, &ThisClass::TargetDestroy);
                UGameplayStatics::ApplyDamage(
                    DetectBoxs[i],
                    AttackDamage,
                    PlayerController,
                    this,
                    UDamageType::StaticClass()
                );
                if (bIsTargetDestroy)
                {
                    i--;
                    CurrentDetectBoxs--;
                    bIsTargetDestroy = false;
                }
           
        }
    }
}

void ATowerDefenceGameType2Character::TargetDestroy(AActor* destroyActor)
{
    Super::TargetDestroy(destroyActor);
   //DetectBoxs.Remove(destroyActor);
 
    
    bIsTargetDestroy = true;

}

float ATowerDefenceGameType2Character::InitializeTower(APlayerController* playerController, FTowerData newTowerData)
{
    Super::InitializeTower(playerController, newTowerData);

    AttackDamage /= 3.5f;
    SpereSize *= 2.0f;
    DetectDistance = 100.0f;
   
    return TowerMoney;
}
