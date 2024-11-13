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
	//유저 위젯은 특이한 생성자를 가짐 
	//이것대로 만들어야 함
	UBoxHpWidget(const FObjectInitializer& ObjectInitializer);

protected:
	//부모 UserWidget 함수
	//UI관련된 모든 기능들이 초기화 되고 이 함수가 호출됨
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }

	FORCEINLINE void SetOwner(class AActor* Owner) { OnwerCharacter = Owner;}

	void UpdateHpBar(float NewCurrentHp);


protected:
	UPROPERTY()
	TObjectPtr<class AActor> OnwerCharacter;
protected:
	//프로그래스 바
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar_Hp;

	//14강 hp바 텍스트 
	/*UPROPERTY()
	TObjectPtr<class UTextBlock> HpStat;*/

	//
	UPROPERTY()
	float MaxHp;

	//14강 현재 hp
	UPROPERTY()
	float CurrentHp;

	
};
