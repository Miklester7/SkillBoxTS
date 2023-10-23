// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_PlantActor.h"
#include "Components/StaticMeshComponent.h"

AEE_PlantActor::AEE_PlantActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScneneComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEE_PlantActor::InitActor(UStaticMesh* Mesh, FVector InitialScale3D)
{
	StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->SetWorldScale3D(InitialScale3D);
}

void AEE_PlantActor::BeginPlay()
{
	Super::BeginPlay();
	
}
