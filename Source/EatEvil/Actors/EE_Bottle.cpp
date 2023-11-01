// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_Bottle.h"
#include "Components/StaticMeshComponent.h"

AEE_Bottle::AEE_Bottle()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneComponent);
}

void AEE_Bottle::SetMesh(UStaticMesh* Mesh)
{
	MeshComponent->SetStaticMesh(Mesh);
}

void AEE_Bottle::EnablePhisics(const FVector& Impuls)
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetSimulatePhysics(true);

	MeshComponent->AddImpulse(Impuls/3.f);
}

void AEE_Bottle::BeginPlay()
{
	Super::BeginPlay();
	//fX?
}

