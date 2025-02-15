// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Region.generated.h"

UCLASS()
class RISKY_API ARegion : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* RegionOwner;

	UPROPERTY(BlueprintReadWrite)
	int32 UnitsInRegion;

	UPROPERTY(EditAnywhere)
	TArray<ARegion*> BorderingRegions;

public:	

	ARegion();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 GetUnits();

	UFUNCTION(BlueprintCallable)
	const ACharacter* GetRegionOwner();

	UFUNCTION(BlueprintCallable)
	const TArray<ARegion*>& GetBorderingRegions();

	UFUNCTION(BlueprintCallable)
	void ChangeOwnerShip(ACharacter* newOwner, int32 unitsAmount);

	UFUNCTION(BlueprintCallable)
	void DeployUnits(int32 unitsAmount);

	UFUNCTION(BlueprintCallable)
	void DecreaseUnitCount(int32 unitsRemoved);
};
