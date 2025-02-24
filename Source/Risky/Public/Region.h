// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Region.generated.h"
class UTextRenderComponent;
class ABaseCharacter;

UCLASS()
class RISKY_API ARegion : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	ABaseCharacter* RegionOwner;

	UPROPERTY(BlueprintReadWrite)
	int32 UnitsInRegion;

	UPROPERTY(EditAnywhere)
	TArray<ARegion*> BorderingRegions;

	UFUNCTION()
	void OnSelectedRegion(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:	

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RegionMesh;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* RegionText;

	UPROPERTY(EditInstanceOnly)
	int OwnerIdStart;

	ARegion();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 GetUnits();

	UFUNCTION(BlueprintCallable)
	const ABaseCharacter* GetRegionOwner();

	UFUNCTION(BlueprintCallable)
	const TArray<ARegion*>& GetBorderingRegions();

	UFUNCTION(BlueprintCallable)
	void ChangeOwnerShip(ABaseCharacter* newOwner, int32 unitsAmount);

	UFUNCTION(BlueprintCallable)
	void DeployUnits(int32 unitsAmount);

	UFUNCTION(BlueprintCallable)
	void DecreaseUnitCount(int32 unitsRemoved);
};
