// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EE_AICharacterBase.h"
#include "Components/EE_DraggingComponent.h"
#include "Animation/EE_AnimNotify_FirstType.h"
#include "Animation/EE_AnimNotify_SecondType.h"
#include "EEUtils.h"
#include "EE_Types.h"
#include "Components/StaticMeshComponent.h"

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

	AttachComponents();
}

void AEE_AICharacterBase::PlayInteractAnim(EActionType Type)
{
	switch (Type)
	{
	case EActionType::Take:
		PlayAnimMontage(TakeAnimMontage);
		break;
	case EActionType::Put:
		PlayAnimMontage(PutAnimMontage);
		break;
	default:
		break;
	}
}

void AEE_AICharacterBase::Action()
{
	DraggingComponent->ExecutableFunction();
}

void AEE_AICharacterBase::AttachComponents()
{
	InstrumentMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	BoxMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

