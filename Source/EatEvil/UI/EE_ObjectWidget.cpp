// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_ObjectWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UEE_ObjectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(ObjectName);
	check(ObjectImage);

	SelectionButton->OnClicked.AddDynamic(this, &UEE_ObjectWidget::Selected);
}

void UEE_ObjectWidget::SetObject(const FObjectInfo& ObjectInfo, const FName& InRowName)
{
	CurrentObject = ObjectInfo;
	ObjectName->SetText(ObjectInfo.PlantName);
	ObjectImage->SetBrushFromTexture(ObjectInfo.Image);
	RowName = InRowName;
}

void UEE_ObjectWidget::Selected()
{
	OnWasSelected.Broadcast(CurrentObject, RowName);
}