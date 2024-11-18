// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIDefenceGameCharacter.h"
#include "DFAIController.h"
#include "Components/WidgetComponent.h"
#include "UI/BoxHpWidget.h"
#include "UI/DFWidgetComponent.h"
#include "DefenceGame/DefenceGamePlayerController.h"
#include "Player/DFPlayerState.h"

AAIDefenceGameCharacter::AAIDefenceGameCharacter()
{
	/*static ConstructorHelpers::FClassFinder<ADFAIController>
		AICONTROLLER(TEXT("/Script/Engine.Blueprint'/Game/DefenceGame/Blueprint/AI/BP_AIController.BP_AIController_C'"));
	if (AICONTROLLER.Class)
	{
		AIControllerClass = AICONTROLLER.Class;
	}*/

	AutoPossessAI = EAutoPossessAI::Disabled;
	
	
	//widget
	HpBar = CreateDefaultSubobject<UDFWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> 
		HpBarWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DefenceGame/Blueprint/UI/BP_BoxHp.BP_BoxHp_C'"));

	//�������� widget ����
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		//����2D�� ����
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		// ���� ũ�� ���⼭ ���� ( �����ٶ� ũ��)
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		//�浹ó��x
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void AAIDefenceGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	ChangeHp(MaxHp);
	
	
}

void AAIDefenceGameCharacter::ChangeHp(float NewHp)
{
	//MAxHp �� �Ѿ�� �ʵ��� ����
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f,MaxHp);
	
	OnHpChanged.Broadcast(CurrentHp);

	if (CurrentHp <= 0.0f)
	{
		OnDead();
	}
}

void AAIDefenceGameCharacter::OnDead()
{
	ADefenceGamePlayerController* playerController = Cast<ADefenceGamePlayerController>(GetWorld()->GetFirstPlayerController());
	ADFPlayerState* playerState = Cast<ADFPlayerState>(playerController->PlayerState);

	playerState->SetMoney(BoxMoney);
	OnHpZero.Broadcast();
	Destroy();
}

float AAIDefenceGameCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float returnValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	//UE_LOG(LogTemp, Warning, TEXT("Damage :%s"), *this->GetName());
	
	float Damaged = CurrentHp - Damage;
	ChangeHp(Damaged);

	return returnValue;

}


void AAIDefenceGameCharacter::SetupCharacterWidget(UUserWidget* InUserWidget)
{
	UBoxHpWidget* HpBarWidget = Cast<UBoxHpWidget>(InUserWidget);
	HpBarWidget->SetMaxHp(MaxHp);
	HpBarWidget->UpdateHpBar(CurrentHp);
	//��������Ʈ�� ���
	OnHpChanged.AddUObject(HpBarWidget, &UBoxHpWidget::UpdateHpBar);
	//OnStatChanged.AddUObject(HpBarWidget, &UABHpBarWidget::UpdateStat);

}

void AAIDefenceGameCharacter::SetUpBox(FBoxData newBoxData)
{
	BoxData = newBoxData;

	MaxHp = BoxData.MaxHp;
	BoxMoney = BoxData.Money;
}


