// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EE_AICharacterBase.h"
#include "Components/EE_DraggingComponent.h"
#include "Animation/EE_AnimNotify_FirstType.h"
#include "Animation/EE_AnimNotify_SecondType.h"
#include "EEUtils.h"
#include "EE_Types.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEE_AICharacterBase::AEE_AICharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DraggingComponent = CreateDefaultSubobject<UEE_DraggingComponent>(TEXT("DraggingComponent"));

	InstrumentMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InstrumentMeshComponent"));
	InstrumentMeshComponent->SetupAttachment(GetRootComponent());

	BoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComponent"));
	BoxMeshComponent->SetupAttachment(GetRootComponent());
}

void AEE_AICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	DraggingComponent->OnReadyToInteract.AddUObject(this, &ThisClass::PlayInteractAnim);

	const auto NotifyFT = EEUtils::FindNotifyByClass<UEE_AnimNotify_FirstType>(TakeAnimMontage);
	if (NotifyFT)
	{
		NotifyFT->OnNotifiedFTypeSignature.AddUObject(this, &ThisClass::Action);
	}

	const auto NotifyST = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(PutAnimMontage);
	if (NotifyST)
	{
		NotifyST->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::Action);
	}

	const auto NotifySTS = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(PutInStorageAnimMontage);
	if (NotifySTS)
	{
		NotifySTS->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::PutInStorage);
	}

	AttachComponents();
}

void AEE_AICharacterBase::PlayInteractAnim(EActionType Type)
{
	switch (Type)
	{
	case EActionType::Take:
		PlayAnimMontage(TakeAnimMontage);
		bIsAnimationPlaying = true;
		BoxMeshComponent->SetVisibility(true);
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
		break;
	case EActionType::Put:
		PlayAnimMontage(PutAnimMontage);
		bIsAnimationPlaying = true;
		InstrumentMeshComponent->SetVisibility(true);
		break;
	case EActionType::PutInStorage:
		PlayAnimMontage(PutInStorageAnimMontage);
		bIsAnimationPlaying = true;
		break;
	default:
		break;
	}
}

void AEE_AICharacterBase::Action(USkeletalMeshComponent* SkeletalMesh)
{
	bIsAnimationPlaying = false;
	DraggingComponent->ExecutableFunction();

	InstrumentMeshComponent->SetVisibility(false);
}

void AEE_AICharacterBase::PutInStorage(USkeletalMeshComponent* SkeletalMesh)
{
	bIsAnimationPlaying = false;
	DraggingComponent->ExecutableFunction();
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	BoxMeshComponent->SetVisibility(false);
}

void AEE_AICharacterBase::AttachComponents()
{
	InstrumentMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	BoxMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

	InstrumentMeshComponent->SetVisibility(false);
	BoxMeshComponent->SetVisibility(false);
}

