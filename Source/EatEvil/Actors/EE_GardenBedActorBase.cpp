// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_GardenBedActorBase.h"
#include "Framework/EE_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "Actors/EE_PlantActor.h"
#include "UI/EE_GardenStatusWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/EE_DraggingComponent.h"
#include "EE_PlayerController.h"

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

	InteractZoneCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractZoneCollision"));
	InteractZoneCollision->SetupAttachment(SceneComponent);
}

void AEE_GardenBedActorBase::SetNewPlant(const FPlantsInfo& PlantInfo, const FName& RowName)
{
	CurrentPlantInfo = PlantInfo;
	PlantRow = RowName;
	Interact();
}

void AEE_GardenBedActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	check(PlantActorClass);
	check(GardenStatusWidgetClass);

	InitWidget();

	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollision->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnCursorOver);
	BoxCollision->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
	BoxCollision->OnReleased.AddDynamic(this, &ThisClass::OnMouseReleased);

	InteractZoneCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::InteractZoneOverlaped);

	if (PlantRow == NAME_None) return;

	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		if (GI->GetPlantInfo(PlantRow, CurrentPlantInfo)) SetPlant();
	}
}

void AEE_GardenBedActorBase::InitWidget()
{
	InteractWidget->SetWidgetClass(GardenStatusWidgetClass);
	const auto StatusWidget = Cast<UEE_GardenStatusWidget>(InteractWidget->GetWidget());
	if (StatusWidget)
	{
		StatusWidget->InitWidget(this);
		StatusWidget->OnWidgetHide.AddUObject(this, &ThisClass::HideWidget);
		StatusWidget->SetOwningActors(this);
		StatusWidget->GetContentDelegate.AddUObject(this, &ThisClass::Interact);
		StatusWidget->OnActionAnyClicked.AddUObject(this, &ThisClass::PlayerInteracted);
		//StatusWidget->GetContentDelegate.AddUObject(this, &ThisClass::GetContent);
	}
	InteractWidget->SetHiddenInGame(true);
}

void AEE_GardenBedActorBase::OnCursorOver(UPrimitiveComponent* TouchedComponent)
{
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
		if (StatusWidget) 
		{
			UpdateStatus(EGardenState::Waiting);
			StatusWidget->UpdateStatus(GardenState);
		}

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
		if (StatusWidget)
		{
			UpdateStatus(EGardenState::Completed);
			StatusWidget->UpdateStatus(GardenState);
		}
		CurrentTime = 0.f;
	}
}

void AEE_GardenBedActorBase::HideWidget()
{
	InteractWidget->SetHiddenInGame(true);
}

void AEE_GardenBedActorBase::GetContent()
{
	const auto StatusWidget = Cast<UEE_GardenStatusWidget>(InteractWidget->GetWidget());
	if (StatusWidget)
	{
		UpdateStatus(EGardenState::Empty);
		StatusWidget->UpdateStatus(GardenState);
	}	
}

void AEE_GardenBedActorBase::InteractZoneOverlaped(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Component = OtherActor->GetComponentByClass(UEE_DraggingComponent::StaticClass());
	if (!Component) return;

	const auto DraggingComponent = Cast<UEE_DraggingComponent>(Component);
	if (!DraggingComponent) return;

	if (DraggingComponent->IsEmployed()) return;

	switch (GardenState)
	{
	case Empty:
	{
		const auto PController = GetWorld()->GetFirstPlayerController<AEE_PlayerController>();
		if (PController)
		{
			//��������� ���������� �������� �� ���������(��� �������������� ����������)
			if (PController->GetAFKPlayer())
			{
				const auto GI = GetGameInstance<UEE_GameInstance>();
				if (GI)
				{
					const auto PlantNames = GI->GetUnblockedPlants();
					const FName RowName = PlantNames[FMath::RandHelper(PlantNames.Num())];
					PlantRow = RowName;
					FPlantsInfo Info;

					if (GI->GetPlantInfo(RowName, Info)) SetNewPlant(Info, RowName);
				}
			}
		}
		DraggingComponent->CanInteract(EActionType::Put, [&]() {return SetPlant(); });
	}
		break;
	case Waiting:
		return;
		break;
	case Completed:
	{
		const FStorageObject ObjectType(PlantRow, Plants.Num(), EObjectType::Plant);
		DraggingComponent->TakeObject(ObjectType, CurrentPlantInfo.PlantName, CurrentPlantInfo.Image);
		DraggingComponent->CanInteract(EActionType::Take, [&]() {return GetContent(); });
	}
		break;
	default:
		break;
	}
}

//ToDo UpdateWidget here
void AEE_GardenBedActorBase::UpdateStatus(EGardenState NewStatus)
{
	GardenState = NewStatus;
	if (GardenState != EGardenState::Waiting)
	{
		bCanInteract = true;
	}
	else
	{
		bCanInteract = false;
	}

	if (GardenState == EGardenState::Empty)
	{
		bIsClear = true;
		PlantRow = NAME_None;
		for (const auto Plant : Plants)
		{
			Plant->Destroy();
		}
		Plants.Empty();
	}
}

void AEE_GardenBedActorBase::Interact()
{
	Super::Interact();
}

void AEE_GardenBedActorBase::PlayerInteracted()
{
	Super::PlayerInteracted();
}
