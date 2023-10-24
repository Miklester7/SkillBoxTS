// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_GardenBedActorBase.h"
#include "Framework/EE_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "Actors/EE_PlantActor.h"
#include "UI/EE_GardenStatusWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AEE_GardenBedActorBaseLog, All, All);

AEE_GardenBedActorBase::AEE_GardenBedActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneComponent);
}

void AEE_GardenBedActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	check(PlantActorClass);
	check(GardenStatusWidgetClass);

	InteractWidget->SetWidgetClass(GardenStatusWidgetClass);
	const auto StatusWidget = Cast<UEE_GardenStatusWidget>(InteractWidget->GetWidget());
	if (StatusWidget)
	{
		StatusWidget->InitWidget(this);
		StatusWidget->OnWidgetHide.AddUObject(this, &ThisClass::HideWidget);
	}
	InteractWidget->SetHiddenInGame(true);


	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollision->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnCursorOver);
	BoxCollision->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
	BoxCollision->OnReleased.AddDynamic(this, &ThisClass::OnMouseReleased);

	if (PlantRow == NAME_None) return;

	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		if (GI->GetPlantInfo(PlantRow, CurrentPlantInfo)) SetPlant();
	}
}

void AEE_GardenBedActorBase::OnCursorOver(UPrimitiveComponent* TouchedComponent)
{
	UE_LOG(AEE_GardenBedActorBaseLog, Warning, TEXT("OnBeginCursorOver"));
	StaticMeshComponent->SetCustomDepthStencilValue(4);
}

void AEE_GardenBedActorBase::OnEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(0);
}

void AEE_GardenBedActorBase::OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	InteractWidget->SetHiddenInGame(false);
}

void AEE_GardenBedActorBase::SetPlant()
{
	if (bIsClear && !SpawnMeshLocations.IsEmpty() && GetWorld())
	{
		const auto StatusWidget = Cast<UEE_GardenStatusWidget>(InteractWidget->GetWidget());
		if (StatusWidget) StatusWidget->UpdateStatus(EGardenState::Waiting);

		bIsClear = false;

		for (const auto& SpwnLocation : SpawnMeshLocations)
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			auto PlActor = GetWorld()->SpawnActor<AEE_PlantActor>(PlantActorClass, SpwnLocation + GetActorLocation(), CurrentPlantInfo.MeshTransform.Rotator(), SpawnParam);
			if (PlActor)
			{
				PlActor->InitActor(CurrentPlantInfo.SpawnObjectMesh, CurrentPlantInfo.MeshTransform.GetScale3D());
				Plants.Add(PlActor);
			}
		}

		GetWorldTimerManager().SetTimer(GrowthRateTimer, this, &ThisClass::GrowthCheck, 1.f, true);
	}
}

void AEE_GardenBedActorBase::GrowthCheck()
{
	CurrentTime++;

	const float Percent = CurrentTime / CurrentPlantInfo.GrowthRate;

	const float NewScale = FMath::Lerp(CurrentPlantInfo.MeshTransform.GetScale3D().X, 1.f, Percent);
	OnTimerUpdated.Broadcast(Percent);

	for (const auto& Plant : Plants)
	{
		Plant->SetScale(NewScale);
	}

	if( CurrentTime >= CurrentPlantInfo.GrowthRate)
	{
		GetWorldTimerManager().ClearTimer(GrowthRateTimer);
		const auto StatusWidget = Cast<UEE_GardenStatusWidget>(InteractWidget->GetWidget());
		if (StatusWidget) StatusWidget->UpdateStatus(EGardenState::Completed);
		CurrentTime = 0.f;
	}
}

void AEE_GardenBedActorBase::HideWidget()
{
	InteractWidget->SetHiddenInGame(true);
}