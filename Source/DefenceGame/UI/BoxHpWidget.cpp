// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BoxHpWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AI/AIDefenceGameCharacter.h"

UBoxHpWidget::UBoxHpWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UBoxHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	////이름으로 찾아서 초기화
	//HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	//ensure(HpProgressBar);
	if (OnwerCharacter)
	{
		AAIDefenceGameCharacter* AICharacter = Cast<AAIDefenceGameCharacter>(OnwerCharacter);
		if (AICharacter)
		{
			
				AICharacter->SetupCharacterWidget(this);

		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	
}

void UBoxHpWidget::UpdateHpBar(float NewCurrentHp)
{
	CurrentHp = NewCurrentHp;
	//ensure(MaxHp > 0.0f);
	if (ProgressBar_Hp)
	{
	

		ProgressBar_Hp->SetPercent(CurrentHp / MaxHp);


	}

	/*if (HpStat)
	{
		HpStat->SetText(FText::FromString(GetHpStatText()));
	}*/

}

