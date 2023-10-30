// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_KettleMenuWidget.h"
#include "UI/EE_CreationWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"

void UEE_KettleMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(CreationWidgetClass);
	check(CreatWidgetsContainer);
	check(CloseButton);

	UpdateWidgets();

	CloseButton->OnClicked.AddDynamic(this, &UEE_KettleMenuWidget::OnCloseButtonClicked);
}

void UEE_KettleMenuWidget::OnCloseButtonClicked()
{
	OnCloseButton.Broadcast();
}

void UEE_KettleMenuWidget::UpdateWidgets()
{
	CreatWidgetsContainer->ClearChildren();

	for (const auto& Name : CraftObjectNames)
	{
		auto CraftWidget = CreateWidget<UEE_CreationWidget>(this, CreationWidgetClass);
		if (CraftWidget)
		{
			CraftWidget->InitWidget(Name);
			CreatWidgetsContainer->AddChild(CraftWidget);
		}
	}
}
