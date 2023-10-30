// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/EE_CreationWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Framework/EE_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(UEE_CreationWidgetLog, All, All);

void UEE_CreationWidget::InitWidget(const FName& RowName)
{
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		ObjectRowName = RowName;
		const auto Recipes = GI->GetUnlockedRecipes();
		if (Recipes.IsEmpty())
		{
			UE_LOG(UEE_CreationWidgetLog, Fatal, TEXT("GetUnlockedRecipes is Empty!"));
			return;
		}
		const auto FindRecipes = Recipes.FilterByPredicate([&](const FPotionRecipes& PotionRecip) {

			return PotionRecip.PotionName == RowName;
			});

		if (FindRecipes.IsEmpty())
		{
			SelectButton->bIsEnabled = false;
		}

		if (!GI->GetPotionInfo(RowName, CurrentObjectInfo))
		{
			UE_LOG(UEE_CreationWidgetLog, Error, TEXT("String not found!"));
			return;
		}

		for (int32 i = 0; i < FindRecipes.Num(); ++i)
		{
			if (CurrentObjectInfo.PotionInfo.IsValidIndex(i))
			{
				switch (i)
				{
				case 0:
					FirstTypeImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[i].Image);
					FirstTypeName->SetText(CurrentObjectInfo.PotionInfo[i].ObjectName);
					FirstTypeButton->bIsEnabled = true;
					CurrentIndex = 0;
					break;

				case 1:
					SecondTypeImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[i].Image);
					SecondTypeName->SetText(CurrentObjectInfo.PotionInfo[i].ObjectName);
					SecondTypeButton->bIsEnabled = true;
					break;
				case 2:
					ThirdTypeImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[i].Image);
					ThirdTypeName->SetText(CurrentObjectInfo.PotionInfo[i].ObjectName);
					ThirdTypeButton->bIsEnabled = true;
					break;
				default:
					break;
				}
			}
		}
		SelectedFirstType();
		ActionStatusName->SetText(FText::FromString("Create"));
	}
}

void UEE_CreationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(FirstTypeButton);
	check(SecondTypeButton);
	check(ThirdTypeButton);
	check(SelectButton);
	check(StartCreateButton);

	FirstTypeButton->bIsEnabled = false;
	SecondTypeButton->bIsEnabled = false;
	ThirdTypeButton->bIsEnabled = false;

	FirstTypeButton->OnClicked.AddDynamic(this, &UEE_CreationWidget::SelectedFirstType);
	SecondTypeButton->OnClicked.AddDynamic(this, &UEE_CreationWidget::SelectedSecondType);
	ThirdTypeButton->OnClicked.AddDynamic(this, &UEE_CreationWidget::SelectedThirdType);

	SelectButton->OnClicked.AddDynamic(this, &UEE_CreationWidget::SelectType);
	ObjectTypesBox->SetVisibility(ESlateVisibility::Collapsed);

	StartCreateButton->OnClicked.AddDynamic(this, &UEE_CreationWidget::CreateObject);
}

void UEE_CreationWidget::SelectedFirstType()
{
	const int8 Index = 0;
	CurrentIndex = Index;
	SelectedObjectImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[Index].Image);
	SelectedObjectName->SetText(CurrentObjectInfo.PotionInfo[Index].ObjectName);
	ObjectTypesBox->SetVisibility(ESlateVisibility::Collapsed);

	UpdateResourceSlot();
}

void UEE_CreationWidget::SelectedSecondType()
{
	const int8 Index = 1;
	CurrentIndex = Index;
	SelectedObjectImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[Index].Image);
	SelectedObjectName->SetText(CurrentObjectInfo.PotionInfo[Index].ObjectName);
	ObjectTypesBox->SetVisibility(ESlateVisibility::Collapsed);

	UpdateResourceSlot();
}

void UEE_CreationWidget::SelectedThirdType()
{
	const int8 Index = 2;
	CurrentIndex = Index;
	SelectedObjectImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[Index].Image);
	SelectedObjectName->SetText(CurrentObjectInfo.PotionInfo[Index].ObjectName);
	ObjectTypesBox->SetVisibility(ESlateVisibility::Collapsed);

	UpdateResourceSlot();
}

void UEE_CreationWidget::SelectType()
{
	ObjectTypesBox->SetVisibility(ESlateVisibility::Visible);
}

void UEE_CreationWidget::CreateObject()
{
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		if (GI->GetFromStorage(CurrentObjectInfo.PotionInfo[CurrentIndex].ResourceRowName, CurrentObjectInfo.PotionInfo[CurrentIndex].ResourcesNum))
		{
			if(!GetWorld()->GetTimerManager().IsTimerActive(CreateTimer))
			{
				GetWorld()->GetTimerManager().SetTimer(CreateTimer, this, &UEE_CreationWidget::TimerUpdated, 0.25f, true);
				ActionStatusName->SetText(FText::FromString(FString::Printf(TEXT("%02.0f%%"), (CurrentTime / CreateTime) * 100.f)));
				StartCreateButton->bIsEnabled = false;
			}
		}
	}
}

void UEE_CreationWidget::TimerUpdated()
{
	CurrentTime = FMath::Clamp(CurrentTime + 0.25f, 0.f, CreateTime);
	const float Percent = CurrentTime / CreateTime;
	ActionStatusName->SetText(FText::FromString(FString::Printf(TEXT("%02.0f%%"), (Percent) * 100.f)));
	CreateProgressBar->SetPercent(Percent);

	if (CurrentTime == CreateTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(CreateTimer);
		CurrentTime = 0.f;
		CreateProgressBar->SetPercent(0.f);
		SetToStorage();
		StartCreateButton->bIsEnabled = true;
		ActionStatusName->SetText(FText::FromString("Create"));
	}
}

void UEE_CreationWidget::SetToStorage()
{
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		const FStorageObject Object(ObjectRowName, 1, EObjectType::Potion);
		GI->PutForStorage(Object);
	}
}

void UEE_CreationWidget::UpdateResourceSlot()
{
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		FPlantsInfo Info;
		if (GI->GetPlantInfo(CurrentObjectInfo.PotionInfo[CurrentIndex].ResourceRowName, Info))
		{
			ResourceImage->SetBrushFromTexture(Info.Image);
		}

		ResurceNum->SetText(FText::FromString(FString::FromInt(CurrentObjectInfo.PotionInfo[CurrentIndex].ResourcesNum)));
	}
}
