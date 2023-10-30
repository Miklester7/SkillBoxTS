// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_GardenStatusWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Actors/EE_GardenBedActorBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Animation/WidgetAnimation.h"
#include "Framework/EE_GameInstance.h"
#include "UI/EE_ObjectWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ScrollBoxSlot.h"
#include "Actors/EE_GardenBedActorBase.h"

DEFINE_LOG_CATEGORY_STATIC(UEE_GardenStatusWidgetLog, All, All);

void UEE_GardenStatusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BarMaterial);
	check(ActionButton);
	check(HideWidgetButton);
	check(ObjectsBox);
	check(ObjectWidgetClass);

	ActionButton->OnClicked.AddDynamic(this, &UEE_GardenStatusWidget::OnActionButtonClicked);
	HideWidgetButton->OnClicked.AddDynamic(this, &UEE_GardenStatusWidget::HideWidget);

	BarMaterialDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), BarMaterial);
	CircleBar->SetBrushFromMaterial(BarMaterialDynamic);
	UpdateStatus(EGardenState::Empty);

	ObjectsBox->ClearChildren();
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
	switch (CurrentState)
	{
	case Empty:
	{
		PlayAnimation(ShowScrollBox);
		if (!ObjectWidgets.IsEmpty())
		{
			ClearObjectWidgets();
		}
		const auto GI = GetGameInstance<UEE_GameInstance>();
		if (GI)
		{
			const auto Plants = GI->GetUnblockedPlants();
			for (const auto& Plant : Plants)
			{
				UEE_ObjectWidget* ObjectWidget = CreateWidget<UEE_ObjectWidget>(this, ObjectWidgetClass);
				if (ObjectWidget)
				{
					FPlantsInfo Info;
					if (GI->GetPlantInfo(Plant, Info)) ObjectWidget->SetObject(Info, Plant);
					ObjectsBox->AddChild(ObjectWidget);
					ObjectWidgets.Add(ObjectWidget);
					ObjectWidget->OnWasSelected.AddUObject(this, &UEE_GardenStatusWidget::PlantWasSelected);

					auto AsSlot = UWidgetLayoutLibrary::SlotAsScrollBoxSlot(ObjectWidget);
					if (AsSlot) AsSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					OnActionAnyClicked.Broadcast();
				}
			}
		}
	}
		break;
	case Waiting:
		break;
	case Completed:
		GetContentDelegate.Broadcast();
		OnActionAnyClicked.Broadcast();
		break;
	default:
		break;
	}
}

void UEE_GardenStatusWidget::HideWidget()
{
	OnWidgetHide.Broadcast();
}

void UEE_GardenStatusWidget::ClearObjectWidgets()
{
	for (const auto Widget : ObjectWidgets)
	{
		Widget->RemoveFromParent();
	}

	ObjectsBox->ClearChildren();
	ObjectWidgets.Empty();
}

void UEE_GardenStatusWidget::PlantWasSelected(const FPlantsInfo& PlantInfo, const FName& RowName)
{
	if (GardenBedActor)
	{
		GardenBedActor->SetNewPlant(PlantInfo, RowName);
	}
}