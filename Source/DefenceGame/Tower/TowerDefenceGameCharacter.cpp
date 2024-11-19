// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerDefenceGameCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DFPlayerState.h"
#include "DefenceGame/DefenceGamePlayerController.h"
#include "Animation/AnimMontage.h"

ATowerDefenceGameCharacter::ATowerDefenceGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
   

    //DetectionSphere->SetupAttachment(GetRootComponent());
    

    DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
    DetectionBox->SetupAttachment(GetCapsuleComponent());
    DetectionBox->SetGenerateOverlapEvents(true);
   // DetectionSphere->SetGenerateOverlapEvents(true);
    AutoPossessAI = EAutoPossessAI::Disabled;
   
}

void ATowerDefenceGameCharacter::BeginPlay()
{
    Super::BeginPlay();

   // SetUpTower();
   /* DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnBeginOverlap);
   
    DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnEndOverlap);*/

    DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnBeginOverlap);

    DetectionBox->OnComponentEndOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnEndOverlap);
}

void ATowerDefenceGameCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (ShowDebug)
    {
       
       /* DrawDebugSphere(GetWorld(), GetActorLocation() + (GetActorForwardVector() * DetectDistance), SpereSize,
            32, FColor::Red, false, 0.1f);*/

       
        // 디버그 박스 그리기
        DrawDebugBox(GetWorld(), GetActorLocation() + (GetActorForwardVector() * DetectDistance), FVector(SpereSize, SpereSize,50.0f), FColor::Green, false, 0.0f);
      /*  DrawDebugBox(GetWorld(), GetActorLocation() + (GetActorForwardVector() * DetectDistance),s,
            32, FColor::Red, false, 0.1f);*/
    }
      

    
}

float ATowerDefenceGameCharacter::InitializeTower(APlayerController* playerController, FTowerData newTowerData)
{
    
    TowerData = newTowerData;
    DetectDistance = TowerData.AttackDistance;

    SpereSize = TowerData.AttackSize;

    CurrentLevel = TowerData.Level;

    AttackDamage = TowerData.AttackDamage;

    AttackDelay = TowerData.AttackDelay;

    TowerMoney = TowerData.TowerMoney;

    NextLevelTowerMoney = TowerData.NextLevelTowerMoney;

    PlayerController = playerController;

    ShowDebug = true;

    return TowerMoney;
}

void ATowerDefenceGameCharacter::SetUpTower()
{

    GetCapsuleComponent()->SetCollisionProfileName("Tower");

   // DetectionSphere->SetSphereRadius(SpereSize);
    //DetectionSphere->SetWorldLocation(TargetPosition);
    FVector ActorLocation = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector TargetPosition = ActorLocation + (ForwardVector * DetectDistance);
  

   

    DetectionBox->SetBoxExtent(FVector(SpereSize, SpereSize, 50.0f));
    DetectionBox->SetWorldLocation(TargetPosition);

    ShowDebug = false;
}

    

void ATowerDefenceGameCharacter::StartAttack()
{
    if (DetectBoxs.Num()>0)
    {

        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        AnimInstance->Montage_Play(AttackAMotion,1.3f);
        //UE_LOG(LogTemp, Warning, TEXT("Attack -> %s"), *DetectBoxs[0]->GetName());
        UGameplayStatics::ApplyDamage(
            DetectBoxs[0],
            AttackDamage,
            PlayerController,
            this,
            UDamageType::StaticClass()
        );
    }
        
}

void ATowerDefenceGameCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        
        if (!DetectBoxs.Contains(OtherActor))
        {
            DetectBoxs.Add(OtherActor);
            //UE_LOG(LogTemp, Warning, TEXT("Add: %s"), *OtherActor->GetName());

            if (!AttackTimerHandle.IsValid())
            {   
                StartAttack();
                GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ATowerDefenceGameCharacter::StartAttack, AttackDelay, true);
            }
                
        }
    }
}

void ATowerDefenceGameCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))
    {
        if (DetectBoxs.Remove(OtherActor) > 0)
        {
            //UE_LOG(LogTemp, Warning, TEXT("Delete: %s"), *OtherActor->GetName());
        }
        if (DetectBoxs.Num()<0)
        {
            GetWorldTimerManager().ClearTimer(AttackTimerHandle);
            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
            AnimInstance->Montage_Stop(1.0f,AttackAMotion);
        }
       
    }
}

void ATowerDefenceGameCharacter::OptionWidget()
{
    K2_OptionWidget();
   
}

void ATowerDefenceGameCharacter::TowerRemove()
{
    ADFPlayerState* playerState = Cast<ADFPlayerState>(PlayerController->PlayerState);
    if (IsValid(playerState))
    {
        playerState->SetMoney(TowerMoney);
        
        Destroy();
    }
}

bool ATowerDefenceGameCharacter::TowerLevelUp(int32 Newlevel)
{

    ADefenceGamePlayerController* dfPlayerController = Cast<ADefenceGamePlayerController>(PlayerController);
    ADFPlayerState* playerState = Cast<ADFPlayerState>(PlayerController->PlayerState);
    if (Newlevel < 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("%d"), Newlevel);
       
        if (NextLevelTowerMoney > playerState->GetMoney())
        {
            UE_LOG(LogTemp, Warning, TEXT("NoMoney"));
            dfPlayerController->SelectTower = NULL;
            K2_OptionWidget();

            return false;
        }
        else
        {
            FTowerData newTowerData = dfPlayerController->GetDataArray(++Newlevel);
            InitializeTower(PlayerController, newTowerData);
            playerState->SetMoney(-TowerMoney);
            SetUpTower();
            dfPlayerController->SelectTower = NULL;
            K2_OptionWidget();
            return true;
        }

    }
    else
    {
        dfPlayerController->SelectTower = NULL;
        K2_OptionWidget();
        return false;
    }
 
}






