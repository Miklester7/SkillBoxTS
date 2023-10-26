#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "EE_Types.generated.h"

class UStaticMesh;

UENUM()
enum EGardenState : uint8
{
	Empty = 0,
	Waiting,
	Completed
};

USTRUCT(BlueprintType)
struct FPlantsInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMesh* SpawnObjectMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	FTransform MeshTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	float GrowthRate{ 60.f };

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FText PlantName;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	UTexture2D* Image;
};

class EATEVIL_API EE_Types : public UBlueprintFunctionLibrary
{

};
