// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Region.generated.h"
class UTextRenderComponent;
class ABaseCharacter;
class AProvince;

UCLASS()
class RISKY_API ARegion : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RegionMesh;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* RegionText;

	UPROPERTY(EditAnywhere)
	USceneComponent* RegionSceneComponent;

	UPROPERTY(EditAnywhere)
	TArray<ARegion*> BorderingRegions;

	UPROPERTY(EditAnywhere)
	AProvince* Province;

	bool IsSelected;

	UFUNCTION()
	void OnSelectedRegion(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	bool IsConnected(ARegion* otherRegion);

	bool Looping(ARegion* otherRegion, TArray<ARegion*>* alreadyVisited);

protected:
	
	UPROPERTY(BlueprintReadWrite)
	ABaseCharacter* RegionOwner;

	UPROPERTY(BlueprintReadWrite)
	int32 UnitsInRegion;

public:	

	ARegion();

	UPROPERTY(EditInstanceOnly)
	int OwnerIdStart;

	UFUNCTION(BlueprintCallable)
	int32 GetUnits();

	UFUNCTION(BlueprintCallable)
	ABaseCharacter* GetRegionOwner();

	UFUNCTION(BlueprintCallable)
	const TArray<ARegion*>& GetBorderingRegions();

	UFUNCTION(BlueprintCallable)
	void ChangeOwnerShip(ABaseCharacter* newOwner, int32 unitsAmount);

	UFUNCTION(BlueprintCallable)
	void DeployUnits(int32 unitsAmount);

	UFUNCTION(BlueprintCallable)
	void DecreaseUnitCount(int32 unitsRemoved);

	bool HasEnoughUnits();

	bool CanAttackThisRegion(ARegion* defendingRegion);

	bool CanFortifyThisRegion(ARegion* otherRegion);

	void ToggleSelection(bool turnOff = false);
};
