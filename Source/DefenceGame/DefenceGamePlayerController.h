// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Struct/TowerData.h"
#include "DefenceGamePlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ADefenceGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefenceGamePlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetTowerRotaionAction;

	/** Jump Input Action */
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IACameraMove;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();


	virtual void Tick(float DeltaSeconds) override;

protected:
	void SetUpGridManager();

	void SetUpCamera();
	
	UFUNCTION(BlueprintCallable, Category = "UI", Meta = (DisplayName = "SetUpPreviewCpp"))
	void SetUpPreview(TSubclassOf<class ATowerDefenceGameCharacter> TowerDefenceCharacterClass);

protected:
	// 마우스 위치에 따른 그리드 셀 계산
	void UpdatePreview();

	void ClickMouseLeft();

	void SpawnTower();

	void ShowTowerOption();

	void SetTowerRotaion(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tower)
	TObjectPtr<class ATowerDefenceGameCharacter> SelectTower;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	TSubclassOf<class ATowerDefenceGameCharacter>PreviewActorClass;
	
	// 현재 프리뷰 액터 인스턴스
	UPROPERTY()
	TObjectPtr<class ATowerDefenceGameCharacter> PreviewActor;


public:
	FORCEINLINE FTowerData GetDataArray(int32 newlevel) { return DataArray[newlevel - 1]; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tower)
	UDataTable* TowerDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<FTowerData> DataArray;

	// 그리드 매니저 참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TObjectPtr<class AGridManager> GridManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	uint8 bIsCanSpawn : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	FVector CanSpawnLocation;

	UPROPERTY()
	float PreviewTowerMoney;


protected:
	void SetCameraMove(const FInputActionValue& Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<class AActor> MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraSpeed;


public:
	UFUNCTION(BlueprintImplementableEvent, Category = "UI",Meta = (DisplayName="OnMoneyChangedCpp"))
	void K2_OnMoneyChanged(float newMoney);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI", Meta = (DisplayName = "NoMoneyAlertCpp"))
	void K2_NoMoneyAlert();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI", Meta = (DisplayName = "OnWaveChangedCpp"))
	void K2_OnWaveChanged(int32 newWave);

public:
	UFUNCTION()
	void OnMoneyChanged(float newMoney);
	
	UFUNCTION()
	void OnWaveChanged(int32 newWave);

	void NoMoneyAlert();

public:
	void SetMoneyWidget();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	uint8 bSelectTower : 1;

	
};


