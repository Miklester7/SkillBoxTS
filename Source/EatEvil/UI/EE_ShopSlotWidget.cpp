// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_ShopSlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UEE_ShopSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(SelectButton);

	SelectButton->OnClicked.AddDynamic(this, &UEE_ShopSlotWidget::ObjectSelect);
}

void UEE_ShopSlotWidget::ObjectSelect()
{
	OnSelected.Broadcast(CurrentImage, ObjectName, ObjectRowName, this, ObjectNum, ObjectGrade);
}

void UEE_ShopSlotWidget::InitWidget(UTexture2D* Image, const FText& InObjectName, const FName& RowName, const int32 InObjectNum, const int8 Grade)
{
	CurrentImage = Image;
	ObjectName = InObjectName;
	ObjectRowName = RowName;
	ObjectNum = InObjectNum;
	ObjectGrade = Grade;

	if (ObjectsNum) ObjectsNum->SetText(FText::FromString(FString::FromInt(ObjectNum)));

	if (ObjectImage && ObjectNameBlock)
	{
		ObjectImage->SetBrushFromTexture(Image);
		ObjectNameBlock->SetText(InObjectName);
	}
}

void UEE_ShopSlotWidget::DisableButton()
{
	SelectButton->bIsEnabled = false;
}


