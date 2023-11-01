// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_ShopActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UI/EE_ShopWidget.h"
#include "Components/EE_NPCStateComponent.h"
#include "Framework/EE_GameInstance.h"
#include "EE_Types.h"
#include "EE_GameMode.h"

AEE_ShopActor::AEE_ShopActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneComponent);

	InteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(SceneComponent);
}

void AEE_ShopActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollision->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnCursorOver);
	BoxCollision->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
	BoxCollision->OnReleased.AddDynamic(this, &ThisClass::OnMouseReleased);

	InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &AEE_ShopActor::OnBeginOverlap);
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

void AEE_ShopActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto NPCStateComponent = OtherActor->GetComponentByClass<UEE_NPCStateComponent>();
	if (NPCStateComponent)
	{
		const auto GI = GetGameInstance<UEE_GameInstance>();
		if (GI)
		{
			const auto Shop = GI->GetAllObjectsFromShop();
			FName DrinkName = NPCStateComponent->GetNeededDrink();
			auto NeededDrink = Shop.FilterByPredicate([&](const FStorageObject& Object) {
				return Object.ObjectRowName == DrinkName;
				});

			if (NeededDrink.IsEmpty())
			{
				DrinkName = NPCStateComponent->CanTakeAlcohol();
				NeededDrink = Shop.FilterByPredicate([&](const FStorageObject& Object) {
					return Object.ObjectRowName == DrinkName;
					});

				if (NeededDrink.IsEmpty())
				{
					NPCStateComponent->ObjectNotFound();
					return;
				}
			}

			int32 Grade = 0;
			for (const auto& Drink : NeededDrink)
			{
				if (Drink.Grade > Grade)
				{
					Grade = Drink.Grade;
				}
			}
			FObjectInfo Info;
			if (GI->GetPotionInfo(DrinkName, Info))
			{
				GI->SetMoney(Info.PotionInfo[Grade].Cost);
				GI->GetFromShop(DrinkName, Grade);
				NPCStateComponent->Drink(DrinkName, Info.PotionInfo[Grade].EffectStrength, Info.PotionInfo[Grade].ObjectMesh);
			}
		}
	}
}
