// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_ShopActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UI/EE_ShopWidget.h"

AEE_ShopActor::AEE_ShopActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneComponent);
}

void AEE_ShopActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollision->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnCursorOver);
	BoxCollision->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
	BoxCollision->OnReleased.AddDynamic(this, &ThisClass::OnMouseReleased);
}

void AEE_ShopActor::OnCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(4);
}

void AEE_ShopActor::OnEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(0);
}

void AEE_ShopActor::OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	const auto ShopWidget = CreateWidget<UEE_ShopWidget>(GetWorld(), ShopWidgetClass);
	if (ShopWidget) ShopWidget->AddToViewport();
}