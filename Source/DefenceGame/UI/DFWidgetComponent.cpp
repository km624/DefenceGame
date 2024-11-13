// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DFWidgetComponent.h"
#include "UI/BoxHpWidget.h"

void UDFWidgetComponent::InitWidget()
{
	Super::InitWidget();

	//GetWidget() 으로 자신에 등록된 위젯 가져옴ㄴ
	UBoxHpWidget* BoxWidget = Cast<UBoxHpWidget>(GetWidget());
	if (BoxWidget)
	{
		//위젯 컴포넌트를 소유하고 있는 액터를 윗에 넘긴다
		BoxWidget->SetOwner(GetOwner());
	}
}
