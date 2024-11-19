// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/SnowBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"

// Sets default values
ASnowBall::ASnowBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 메쉬 컴포넌트 초기화
   
    // 이동 컴포넌트 초기화
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bShouldBounce = false;

}

// Called when the game starts or when spawned
void ASnowBall::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASnowBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



