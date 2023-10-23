// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_GardenBedActorBase.h"
#include "Framework/EE_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "Actors/EE_PlantActor.h"

DEFINE_LOG_CATEGORY_STATIC(AEE_GardenBedActorBaseLog, All, All);

AEE_GardenBedActorBase::AEE_GardenBedActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(SceneComponent);
}

void AEE_GardenBedActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	check(PlantActorClass);

	OnBeginCursorOver.AddDynamic(this, &ThisClass::Test);

	if (PlantRow == NAME_None) return;

	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		if (GI->GetPlantInfo(PlantRow, CurrentPlantInfo)) SetPlant();
	}
}

void AEE_GardenBedActorBase::Test(AActor* TouchedActor)
{
	UE_LOG(AEE_GardenBedActorBaseLog, Warning, TEXT("OnBeginCursorOver"));
}

void AEE_GardenBedActorBase::SetPlant()
{
	if (bIsClear && !SpawnMeshLocations.IsEmpty() && GetWorld())
	{
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
	}
}

