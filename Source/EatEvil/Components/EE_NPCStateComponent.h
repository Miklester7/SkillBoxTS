// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EE_NPCStateComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnStatesUpdated, const float, const float, const float);
DECLARE_MULTICAST_DELEGATE(FOnObjectNotFoud);
DECLARE_MULTICAST_DELEGATE(FOnDrink);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDrunk,bool);

class UStaticMesh;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EATEVIL_API UEE_NPCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEE_NPCStateComponent();

	const FName& GetNeededDrink();
	const FName& CanTakeAlcohol();

	void ObjectNotFound();

	void Drink(const FName& DrinkName,const float Effect,UStaticMesh* Mesh);
	FOnStatesUpdated OnStatesUpdated;
	FOnObjectNotFoud OnObjectNotFoud;
	FOnDrink OnDrink;
	FOnDrunk OnDrunk;

	UPROPERTY()
	TObjectPtr<UStaticMesh> CurrentMesh;

	bool Use();
protected:
	virtual void BeginPlay() override;

private:
	float Alcohol{ 0.f };
	FName AlcoholRowName = "Alcohol";

	float AntiAlcohol{ 0.f };
	FName AntiAlcoholRowName = "AntiAlcohol";

	float Nutrients{ 1.f };
	FName NutrientsRowName = "NutritiousDrink";

	FTimerHandle UpdateTimer;

	bool Drunk{ false };
private:
	void Update();

	FName CurrentName;
	float CurrentEffect{ 1.f };
		
};
