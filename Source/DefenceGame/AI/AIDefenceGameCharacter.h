// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefenceGameCharacter.h"
#include "Struct/BoxData.h"
#include "AIDefenceGameCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);

UCLASS()
class DEFENCEGAME_API AAIDefenceGameCharacter : public ADefenceGameCharacter
{
	GENERATED_BODY()

public:
	AAIDefenceGameCharacter();

public:
	virtual void BeginPlay() override;
	FORCEINLINE void SetMaxHp(float Newhp) { MaxHp = Newhp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }

	FORCEINLINE float GetBoxMoney() { return BoxMoney; }
	void ChangeHp(float NewHp);

	void OnDead();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> StaticComp;

	TObjectPtr<UStaticMesh> staticMesh;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float BoxMoney;

public:
	void SetUpBox(FBoxData newBoxData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	FBoxData BoxData;

protected:
	TObjectPtr<class USoundBase> BoxDestroySound;

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TObjectPtr<class UNiagaraSystem> FXSystem;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TObjectPtr<class UNiagaraComponent> FXComponent;
	

};
