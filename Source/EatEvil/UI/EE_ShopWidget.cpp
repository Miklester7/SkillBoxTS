// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_ShopWidget.h"
#include "Components/ScrollBox.h"
#include "Framework/EE_GameInstance.h"
#include "UI/EE_ShopSlotWidget.h"
#include "EE_Types.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UEE_ShopWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(ShopSlotWidgetClass);
	check(ForSaleButton);
	
	ForSaleButton->OnClicked.AddDynamic(this, &UEE_ShopWidget::SendToStore);

	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		GI->OnStorageUpdated.AddUObject(this, &UEE_ShopWidget::UpdateStorageWidgets);
		GI->OnShopUpdated.AddUObject(this, &UEE_ShopWidget::UpdateShopWidgets);
	}

	UpdateStorageWidgets();
	UpdateShopWidgets();
}

void UEE_ShopWidget::OnObjectSelected(UTexture2D* InImage, const FText& InObjectName, const FName& RowName, UEE_ShopSlotWidget* Widget, const int32 Num, const int8 Grade)
{
	SelectedWidget = Widget;
	Image = InImage;
	ObjName = InObjectName;
	ObjRow = RowName;
	ObjNum = Num;
	ObjGrade = Grade;

	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (!GI) return;

	int32 PowerValue;
	int32 TriggersNum;
	FText DescriptionText;
	int32 Cost;

	if (Grade >= 0)
	{
		UpdateTextForPotion();

		FObjectInfo Info;

		if (GI->GetPotionInfo(RowName, Info))
		{
			PowerValue = Info.PotionInfo[Grade].EffectStrength;
			TriggersNum = Info.PotionInfo[Grade].NumberOfUses;
			DescriptionText = Info.PotionInfo[Grade].Description;
			Cost = Info.PotionInfo[Grade].Cost;
			PowerResult->SetText(FText::FromString(FString::FromInt(PowerValue)));
			NumTriggersResult->SetText(FText::FromString(FString::FromInt(TriggersNum)));
		}
	}
	else
	{
		UpdateTextForPlant();
		//todo fromText
		Cost = 2;
		DescriptionText = FText::FromString(FString("Sell wholesale"));
	}

	ObjectImage->SetBrushFromTexture(InImage);
	ObjectNameText->SetText(InObjectName);
	Description->SetText(DescriptionText);

	const auto Multiplier = GI->GetPriceMultiplier();
	if(Multiplier != 0.f) Cost *= Multiplier;
	
	CostTextResult->SetText(FText::FromString(FString::Printf(TEXT("%i+(%02.0f%%)"), Cost, Multiplier)));
}

void UEE_ShopWidget::SendToStore()
{
	if (SelectedWidget)
	{
		SelectedWidget->RemoveFromParent();
	}
	else return;
	SelectedWidget = nullptr;

	
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		if (ObjGrade < 0)
		{
			GI->GetFromStorage(ObjRow, ObjNum);
			GI->SetMoney(ObjNum * 2);
		}
		GI->SendToShop(ObjRow, ObjGrade);
	}
	
	UpdateShopWidgets();
}

void UEE_ShopWidget::UpdateStorageWidgets()
{
	StorageContainer->ClearChildren();
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		const auto Objects = GI->GetAllObjectsFromStorage();
		for (const auto& Object : Objects)
		{
			if (Object.Quantity == 0) continue;

			auto ShopSlot = CreateWidget<UEE_ShopSlotWidget>(this, ShopSlotWidgetClass);
			if (ShopSlot)
			{
				UTexture2D* FindImage = nullptr;
				FText ObjectName;

				switch (Object.ObjectType)
				{
				case EObjectType::Plant:
				{
					FPlantsInfo Info;
					if (GI->GetPlantInfo(Object.ObjectRowName, Info))
					{
						FindImage = Info.Image;
						ObjectName = Info.PlantName;
					}
				}
				break;
				case EObjectType::Potion:
				{
					FObjectInfo Info;
					if (GI->GetPotionInfo(Object.ObjectRowName, Info))
					{
						FindImage = Info.PotionInfo[Object.Grade].Image;
						ObjectName = Info.PotionInfo[Object.Grade].ObjectName;
					}
				}
				break;
				case EObjectType::Weapon:

					break;
				default:
					break;
				}
				ShopSlot->InitWidget(FindImage, ObjectName, Object.ObjectRowName, Object.Quantity, Object.Grade);
				ShopSlot->OnSelected.AddUObject(this, &UEE_ShopWidget::OnObjectSelected);
				StorageContainer->AddChild(ShopSlot);
			}
		}
	}
}

void UEE_ShopWidget::UpdateShopWidgets()
{
	ShopContainer->ClearChildren();
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		const auto Objects = GI->GetAllObjectsFromShop();
		for (const auto& Object : Objects)
		{
			if (Object.Quantity == 0) continue;

			auto ShopSlot = CreateWidget<UEE_ShopSlotWidget>(this, ShopSlotWidgetClass);
			if (ShopSlot)
			{
				UTexture2D* FindImage = nullptr;
				FText ObjectName;

				switch (Object.ObjectType)
				{
				case EObjectType::Plant:
				{
					FPlantsInfo Info;
					if (GI->GetPlantInfo(Object.ObjectRowName, Info))
					{
						FindImage = Info.Image;
						ObjectName = Info.PlantName;
					}
				}
				break;
				case EObjectType::Potion:
				{
					FObjectInfo Info;
					if (GI->GetPotionInfo(Object.ObjectRowName, Info))
					{
						FindImage = Info.PotionInfo[Object.Grade].Image;
						ObjectName = Info.PotionInfo[Object.Grade].ObjectName;
					}
				}
				break;
				case EObjectType::Weapon:

					break;
				default:
					break;
				}
				ShopSlot->InitWidget(FindImage, ObjectName, Object.ObjectRowName, Object.Quantity, Object.Grade);
				ShopSlot->DisableButton();
				ShopSlot->OnSelected.AddUObject(this, &UEE_ShopWidget::OnObjectSelected);
				ShopContainer->AddChild(ShopSlot);
			}
		}
	}
}

void UEE_ShopWidget::UpdateTextForPotion()
{
	NumberTriggersName->SetText(FText::FromString(FString("Number of uses:")));
	Power->SetText(FText::FromString(FString("Effect strength:")));
}

void UEE_ShopWidget::UpdateTextForPlant()
{
	NumberTriggersName->SetText(FText::FromString(FString("")));
	Power->SetText(FText::FromString(FString("")));
	NumTriggersResult->SetText(FText::FromString(FString("")));
	PowerResult->SetText(FText::FromString(FString("")));;
}
