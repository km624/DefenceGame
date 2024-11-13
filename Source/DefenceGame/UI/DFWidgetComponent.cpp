// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DFWidgetComponent.h"
#include "UI/BoxHpWidget.h"

void UDFWidgetComponent::InitWidget()
{
	Super::InitWidget();

	//GetWidget() ���� �ڽſ� ��ϵ� ���� �����Ȥ�
	UBoxHpWidget* BoxWidget = Cast<UBoxHpWidget>(GetWidget());
	if (BoxWidget)
	{
		//���� ������Ʈ�� �����ϰ� �ִ� ���͸� ���� �ѱ��
		BoxWidget->SetOwner(GetOwner());
	}
}
