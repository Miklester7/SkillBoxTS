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

UENUM()
enum EActionType : uint8
{
	Take,
	Put,
	PutInStorage,

};

UENUM()
enum EObjectType : uint8
{
	Plant,
	Potion,
	Weapon
};

UENUM()
enum EEffectType : uint8
{
	Power,
	Health,

};

USTRUCT()
struct FStorageObject
{
	GENERATED_BODY()

	FStorageObject(const FName& InObjectRowName, const int32& InQuantity,const EObjectType& InObjectType) : ObjectRowName(InObjectRowName), Quantity(InQuantity), ObjectType(InObjectType){};
	FStorageObject(const FName& InObjectRowName, const int32& InQuantity,const EObjectType& InObjectType,const int8 ObjectGrade) : ObjectRowName(InObjectRowName), Quantity(InQuantity), ObjectType(InObjectType), Grade(ObjectGrade){};
	FStorageObject() { };

	FName ObjectRowName;
	int32 Quantity;
	EObjectType ObjectType;
	int8 Grade = -1;
};

USTRUCT(BlueprintType)
struct FPotionRecipes
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Category = "Name")
	FName PotionName;

	UPROPERTY(EditDefaultsOnly, Category = "Grade")
	int32 Grade;
};

USTRUCT(BlueprintType)
struct FPotionInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float EffectStrength{ 10.f };

	UPROPERTY(EditDefaultsOnly, Category = "Create")
	FText Description;

	UPROPERTY(EditDefaultsOnly, Category = "Create")
	int32 NumberOfUses{ 1 };

	UPROPERTY(EditDefaultsOnly, Category = "Create")
	int32 ResourcesNum{ 5 };

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FText ObjectName;

	UPROPERTY(EditDefaultsOnly, Category = "Create")
	FText ResourceName;

	UPROPERTY(EditDefaultsOnly, Category = "Create")
	FName ResourceRowName;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	int32 Cost{ 100 };
};

USTRUCT(BlueprintType)
struct FObjectInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Category = "Info")
	TArray<FPotionInfo> PotionInfo;
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
