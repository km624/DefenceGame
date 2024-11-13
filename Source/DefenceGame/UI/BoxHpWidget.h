// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UBoxHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//���� ������ Ư���� �����ڸ� ���� 
	//�̰ʹ�� ������ ��
	UBoxHpWidget(const FObjectInitializer& ObjectInitializer);

protected:
	//�θ� UserWidget �Լ�
	//UI���õ� ��� ��ɵ��� �ʱ�ȭ �ǰ� �� �Լ��� ȣ���
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }

	FORCEINLINE void SetOwner(class AActor* Owner) { OnwerCharacter = Owner;}

	void UpdateHpBar(float NewCurrentHp);


protected:
	UPROPERTY()
	TObjectPtr<class AActor> OnwerCharacter;
protected:
	//���α׷��� ��
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar_Hp;

	//14�� hp�� �ؽ�Ʈ 
	/*UPROPERTY()
	TObjectPtr<class UTextBlock> HpStat;*/

	//
	UPROPERTY()
	float MaxHp;

	//14�� ���� hp
	UPROPERTY()
	float CurrentHp;

	
};
