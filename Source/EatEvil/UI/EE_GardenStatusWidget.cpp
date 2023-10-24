// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_GardenStatusWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Actors/EE_GardenBedActorBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

DEFINE_LOG_CATEGORY_STATIC(UEE_GardenStatusWidgetLog, All, All);

void UEE_GardenStatusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BarMaterial);
	check(ActionButton);
	check(HideWidgetButton);

	ActionButton->OnClicked.AddDynamic(this, &UEE_GardenStatusWidget::OnActionButtonClicked);
	HideWidgetButton->OnClicked.AddDynamic(this, &UEE_GardenStatusWidget::HideWidget);

	BarMaterialDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), BarMaterial);
	CircleBar->SetBrushFromMaterial(BarMaterialDynamic);
	UpdateStatus(EGardenState::Empty);
}

void UEE_GardenStatusWidget::InitWidget(AEE_GardenBedActorBase* OwnerActor)
{
	OwnerActor->OnTimerUpdated.AddUObject(this, &UEE_GardenStatusWidget::UpdateTimer);
}

void UEE_GardenStatusWidget::UpdateTimer(float Percent)
{
	BarMaterialDynamic->SetScalarParameterValue(FName("Percent"), Percent);
	if (StatusText) StatusText->SetText(FText::FromString(FString::Printf(TEXT("%02.0f%%"), Percent * 100.f)));
}

void UEE_GardenStatusWidget::UpdateStatus(EGardenState State)
{
	CurrentState = State;

	switch (CurrentState)
	{
	case Empty:
		BarMaterialDynamic->SetScalarParameterValue(FName("Percent"), 0.f);
		if (StatusText) StatusText->SetText(FText::FromString("+"));
		break;
	case Waiting:
		if (StatusText) StatusText->SetText(FText::FromString("00%"));
		break;
	case Completed:
		if (StatusText) StatusText->SetText(FText::FromString("Completed"));
		break;
	default:
		break;
	}

}

void UEE_GardenStatusWidget::OnActionButtonClicked()
{
	UE_LOG(UEE_GardenStatusWidgetLog, Error, TEXT("ButtonClicked!"));
}

void UEE_GardenStatusWidget::HideWidget()
{
	OnWidgetHide.Broadcast();
}
