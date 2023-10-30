// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_GardenBedPurchased.h"
#include "Components/WidgetComponent.h"
#include "UI/EE_LandPurchaseWidget.h"

AEE_GardenBedPurchased::AEE_GardenBedPurchased()
{
	PrimaryActorTick.bCanEverTick = false;

	GarbageMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GarbageMesh"));
	GarbageMeshComponent->SetupAttachment(GetRootComponent());
	GarbageMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEE_GardenBedPurchased::BeginPlay()
{
	check(LandPurchaseWidgetClass);

	Super::BeginPlay();
	
	bCanInteract = false;
}

void AEE_GardenBedPurchased::InitWidget()
{
	if (Purchased)
	{
		Super::InitWidget();
	}
	else
	{
		InteractWidget->SetWidgetClass(LandPurchaseWidgetClass);
		const auto PWidget = Cast<UEE_LandPurchaseWidget>(InteractWidget->GetWidget());
		if (PWidget)
		{
			PWidget->OnPurchased.AddUObject(this, &AEE_GardenBedPurchased::UnlockPlace);
			PWidget->OnHide.AddUObject(this, &AEE_GardenBedPurchased::HideWidget);
		}
		InteractWidget->SetHiddenInGame(true);
	}
}

void AEE_GardenBedPurchased::InteractZoneOverlaped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Purchased) Super::InteractZoneOverlaped(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


void AEE_GardenBedPurchased::UnlockPlace()
{
	Purchased = true;
	
	GarbageMeshComponent->SetHiddenInGame(true);
	InitWidget();
	bCanInteract = true;
}

void AEE_GardenBedPurchased::HideWidget()
{
	InteractWidget->SetHiddenInGame(true);
}
