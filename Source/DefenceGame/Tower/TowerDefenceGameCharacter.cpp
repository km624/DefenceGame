// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerDefenceGameCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"

ATowerDefenceGameCharacter::ATowerDefenceGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	/*DetectionSphere->InitSphereRadius(SpereSize);
    DetectionSphere->SetRelativeLocation(GetActorForwardVector() * DetectDistance);*/

    //DetectionSphere->SetupAttachment(GetRootComponent());
    DetectionSphere->SetupAttachment(GetCapsuleComponent());
    //DetectionSphere->SetCollisionProfileName(TEXT("OverlapAll"));

    
    DetectionSphere->SetGenerateOverlapEvents(true);
    AutoPossessAI = EAutoPossessAI::Disabled;
   
}

void ATowerDefenceGameCharacter::BeginPlay()
{
    Super::BeginPlay();

   // SetUpTower();
    DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnBeginOverlap);
   
    DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnEndOverlap);
}

void ATowerDefenceGameCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation()+(GetActorForwardVector()* DetectDistance), SpereSize,
        32, FColor::Red, false, 0.1f);
}

void ATowerDefenceGameCharacter::SetUpTower()
{
    DetectionSphere->SetSphereRadius(SpereSize);

    FVector ActorLocation = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector TargetPosition = ActorLocation + (ForwardVector * DetectDistance);
    DetectionSphere->SetWorldLocation(TargetPosition);
    //DetectionSphere->SetRelativeLocation(GetActorForwardVector() * DetectDistance);
}

void ATowerDefenceGameCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        
        if (!DetectBoxs.Contains(OtherActor))
        {
            DetectBoxs.Add(OtherActor);
            UE_LOG(LogTemp, Warning, TEXT("Add: %s"), *OtherActor->GetName());
        }
    }
}

void ATowerDefenceGameCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))
    {
        if (DetectBoxs.Remove(OtherActor) > 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("Delete: %s"), *OtherActor->GetName());
        }
    }
}
