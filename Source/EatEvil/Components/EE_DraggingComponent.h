// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EE_DraggingComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTakeObject,const FName&,const FText&,UTexture2D*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPutObject,const FName&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EATEVIL_API UEE_DraggingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEE_DraggingComponent();

	void TakeObject(const FName& RowName,const FText& ObjectGameName, UTexture2D* Image);
	void PutObject(const FName& RowName);

	FOnTakeObject OnTakeObject;
	FOnPutObject OnPutObject;
protected:
	virtual void BeginPlay() override;
		
};
