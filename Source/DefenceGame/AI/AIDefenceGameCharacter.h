// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefenceGameCharacter.h"
#include "AIDefenceGameCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);

UCLASS()
class DEFENCEGAME_API AAIDefenceGameCharacter : public ADefenceGameCharacter
{
	GENERATED_BODY()

public:
	AAIDefenceGameCharacter();

	FORCEINLINE void SetMaxHp(float Newhp) { MaxHp = Newhp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }

	void ChangeHp(float NewHp);

public:
	FOnHpChangedDelegate OnHpChanged;
	FOnHpZeroDelegate OnHpZero;

protected:
	// ¸¸µç À§Á¬ ºÙÈú¶§ »ç¿ëÇÏ´Â À§Á¬ ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDFWidgetComponent> HpBar;

public:
	
	void SetupCharacterWidget(class UUserWidget* InUserWidget);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float CurrentHp;

protected:

	
};
