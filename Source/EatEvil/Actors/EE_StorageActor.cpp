// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_StorageActor.h"
#include "Components/BoxComponent.h"
#include "Components/EE_DraggingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Framework/EE_GameInstance.h"

AEE_StorageActor::AEE_StorageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	InteractZoneCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractZoneCollision"));
	InteractZoneCollision->SetupAttachment(SceneComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
}

void AEE_StorageActor::BeginPlay()
{
	Super::BeginPlay();

	InteractZoneCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollision->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnCursorOver);
	BoxCollision->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEngCursorOver);
}

void AEE_StorageActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Component = OtherActor->GetComponentByClass(UEE_DraggingComponent::StaticClass());
	if (Component)
	{
		const auto DraggingComponent = Cast<UEE_DraggingComponent>(Component);
		if (DraggingComponent)
		{
			
			if(!DraggingComponent->PutObject(CurrentObject)) return;

			DraggingComponent->CanInteract(EActionType::Put, [&]() { return PutForStorage(); });
			DraggingComponent->ClearObject();
		}
	}
}

void AEE_StorageActor::OnCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(4);
}

void AEE_StorageActor::OnEngCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(0);
}

void AEE_StorageActor::PutForStorage()
{
	auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		GI->PutForStorage(CurrentObject);
		CurrentObject.ObjectRowName = NAME_None;
	}
}
