// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EE_AINPC_Character.h"
#include "Components/EE_NPCStateComponent.h"
#include "UI/EE_NPSStatusWidget.h"
#include "Components/WidgetComponent.h"
#include "EEUtils.h"
#include "Animation/EE_AnimNotify_FirstType.h"
#include "Animation/EE_AnimNotify_SecondType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/EE_Bottle.h"

AEE_AINPC_Character::AEE_AINPC_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	NPCStateComponent = CreateDefaultSubobject<UEE_NPCStateComponent>(TEXT("NPCStateComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NPSStatusWidget"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void AEE_AINPC_Character::Action()
{
	if (!NPCStateComponent->CurrentMesh) return;

	NPCStateComponent->OnDrunk.AddUObject(this, &AEE_AINPC_Character::SetDrunk);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	if (BottleActorClass && GetWorld())
	{
		auto BottleActor = GetWorld()->SpawnActorDeferred<AEE_Bottle>(BottleActorClass, FTransform());
		if (BottleActor)
		{
			BottleActor->SetMesh(NPCStateComponent->CurrentMesh);
			BottleActor->FinishSpawning(FTransform());
			BottleActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
			CurrentBottleActor = BottleActor;
			NPCStateComponent->CurrentMesh = nullptr;
		}
	}
	PlayAnimMontage(DrinkAnimMontage);
}

void AEE_AINPC_Character::BeginPlay()
{
	Super::BeginPlay();
	
	check(NPSStatusWidgetClass);
	check(BottleActorClass);

	WidgetComponent->SetWidgetClass(NPSStatusWidgetClass);
	auto Widget = Cast<UEE_NPSStatusWidget>(WidgetComponent->GetWidget());
	if (Widget) 
	{
		Widget->SetupComponent(NPCStateComponent);
		Widget->UpdateWidget(0.f, 0.f, 1.f);
	}

	const auto NotifyFT = EEUtils::FindNotifyByClass<UEE_AnimNotify_FirstType>(DrinkAnimMontage);
	if (NotifyFT)
	{
		NotifyFT->OnNotifiedFTypeSignature.AddUObject(this, &ThisClass::PlaySecondAnimMontage);
	}

	const auto NotifyST = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(ThrowAnimMontage);
	if (NotifyST)
	{
		NotifyST->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::ActionEnd);
	}

	const auto NotifySTS = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(SleepAnimMontage);
	if (NotifySTS)
	{
		NotifySTS->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::PlayUpMontage);
	}
	
	const auto NotifySTSt = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(UpAnimMontage);
	if (NotifySTSt)
	{
		NotifySTSt->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::ReturnMovement);
	}
}

void AEE_AINPC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEE_AINPC_Character::ActionEnd(USkeletalMeshComponent* SkeletalMesh)
{
	if (GetMesh() != SkeletalMesh) return;

	if (CurrentBottleActor)
	{
		CurrentBottleActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentBottleActor->EnablePhisics(GetActorLocation());
		CurrentBottleActor->SetLifeSpan(30.f);
		CurrentBottleActor = nullptr;
		if (!NPCStateComponent->Use())
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
}

void AEE_AINPC_Character::PlaySecondAnimMontage(USkeletalMeshComponent* SkeletalMesh)
{
	if (GetMesh() != SkeletalMesh) return;

	PlayAnimMontage(ThrowAnimMontage);
}

void AEE_AINPC_Character::SetDrunk(bool Value)
{
	Drunk = Value;
	if (Drunk)
	{
		GetCharacterMovement()->MaxWalkSpeed = 100.f;
		PlayAnimMontage(SleepAnimMontage);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 250.f;
	}
}

void AEE_AINPC_Character::ReturnMovement(USkeletalMeshComponent* SkeletalMesh)
{
	if (GetMesh() != SkeletalMesh) return;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AEE_AINPC_Character::PlayUpMontage(USkeletalMeshComponent* SkeletalMesh)
{
	if (GetMesh() != SkeletalMesh) return;

	PlayAnimMontage(UpAnimMontage);
}

