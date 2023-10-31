// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_KettleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/EE_KettleMenuWidget.h"
#include "Characters/EE_AICharacterBase.h"

AEE_KettleActor::AEE_KettleActor()
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

void AEE_KettleActor::Interact()
{
	Super::Interact();
}

void AEE_KettleActor::BeginPlay()
{
	Super::BeginPlay();

	check(KettleMenuWidgetClass);

	InteractWidget->SetWidgetClass(KettleMenuWidgetClass);
	const auto IntWidget = Cast<UEE_KettleMenuWidget>(InteractWidget->GetWidget());
	if (IntWidget)
	{
		IntWidget->OnCloseButton.AddUObject(this, &AEE_KettleActor::HideWidget);
		InteractWidget->SetHiddenInGame(true);
	}

	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollision->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnCursorOver);
	BoxCollision->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
	BoxCollision->OnReleased.AddDynamic(this, &ThisClass::OnMouseReleased);

}

void AEE_KettleActor::HideWidget()
{
	InteractWidget->SetHiddenInGame(true);
}

void AEE_KettleActor::OnCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(4);
}

void AEE_KettleActor::OnEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMeshComponent->SetCustomDepthStencilValue(0);
}

void AEE_KettleActor::OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	InteractWidget->SetHiddenInGame(false);
}

