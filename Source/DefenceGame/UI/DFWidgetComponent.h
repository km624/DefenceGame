// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DFWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UDFWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
protected:

	virtual void InitWidget() override;
	
};
