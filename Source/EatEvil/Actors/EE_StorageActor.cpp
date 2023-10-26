// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_StorageActor.h"
#include "Components/BoxComponent.h"
#include "Components/EE_DraggingComponent.h"

AEE_StorageActor::AEE_StorageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	InteractZoneCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractZoneCollision"));
	InteractZoneCollision->SetupAttachment(SceneComponent);
}

void AEE_StorageActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractZoneCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
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
			//DraggingComponent->PutObject();
		}
	}
}
