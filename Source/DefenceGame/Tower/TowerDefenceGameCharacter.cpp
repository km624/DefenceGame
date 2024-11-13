// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerDefenceGameCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

ATowerDefenceGameCharacter::ATowerDefenceGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	//DetectionSphere->InitSphereRadius(300.0f);
    //DetectionSphere->SetRelativeLocation(GetActorForwardVector() * DetectDistance);
    DetectionSphere->SetupAttachment(GetRootComponent());

    //DetectionSphere->SetCollisionProfileName(TEXT("OverlapAll"));

    
    DetectionSphere->SetGenerateOverlapEvents(true);
    AutoPossessAI = EAutoPossessAI::Disabled;
   
}

void ATowerDefenceGameCharacter::BeginPlay()
{
    Super::BeginPlay();

    SetUpTower(DetectDistance, SpereSize);
    DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnBeginOverlap);
   
    DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerDefenceGameCharacter::OnEndOverlap);
}

void ATowerDefenceGameCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation()+(GetActorForwardVector()* DetectDistance), DetectionSphere->GetUnscaledSphereRadius(),
        32, FColor::Red, false, 0.1f);
}

void ATowerDefenceGameCharacter::SetUpTower(float Distance, float size)
{
    DetectionSphere->SetSphereRadius(size);
    DetectionSphere->SetRelativeLocation(GetActorForwardVector() * Distance);
}

void ATowerDefenceGameCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        // 콘솔에 겹침된 액터 이름 출력
        UE_LOG(LogTemp, Warning, TEXT("actorName: %s"), *OtherActor->GetName());
    }
}

void ATowerDefenceGameCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
