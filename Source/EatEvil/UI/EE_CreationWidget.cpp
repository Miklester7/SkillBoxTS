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
	ObjectTypesBox->SetVisibility(ESlateVisibility::HitTestInvisible);

	StartCreateButton->OnClicked.AddDynamic(this, &UEE_CreationWidget::CreateObject);
}

void UEE_CreationWidget::SelectedFirstType()
{
	const int8 Index = 0;
	CurrentIndex = Index;
	SelectedObjectImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[Index].Image);
	SelectedObjectName->SetText(CurrentObjectInfo.PotionInfo[Index].ObjectName);
	ObjectTypesBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEE_CreationWidget::SelectedSecondType()
{
	const int8 Index = 1;
	CurrentIndex = Index;
	SelectedObjectImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[Index].Image);
	SelectedObjectName->SetText(CurrentObjectInfo.PotionInfo[Index].ObjectName);
	ObjectTypesBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEE_CreationWidget::SelectedThirdType()
{
	const int8 Index = 2;
	CurrentIndex = Index;
	SelectedObjectImage->SetBrushFromTexture(CurrentObjectInfo.PotionInfo[Index].Image);
	SelectedObjectName->SetText(CurrentObjectInfo.PotionInfo[Index].ObjectName);
	ObjectTypesBox->SetVisibility(ESlateVisibility::HitTestInvisible);
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
		if (GI->GetFromStorage(ObjectRowName, CurrentObjectInfo.PotionInfo[CurrentIndex].ResourcesNum))
		{
			GetWorld()->GetTimerManager().SetTimer(CreateTimer, this, &UEE_CreationWidget::TimerUpdated, 0.25f, true);
			StartCreateButton->bIsEnabled = false;
		}
	}
}

void UEE_CreationWidget::TimerUpdated()
{
	CurrentTime = FMath::Max(CurrentTime + 0.25f, CreateTime);
	ActionStatusName->SetText(FText::FromString(FString::Printf(TEXT("%02.0f%%"), CurrentTime/ CreateTime * 100.f)));

	if (CurrentTime == CreateTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(CreateTimer);
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