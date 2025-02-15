// Fill out your copyright notice in the Description page of Project Settings.


#include "Region.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARegion::ARegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARegion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ARegion::GetUnits()
{
	return UnitsInRegion;
}

const ACharacter* ARegion::GetRegionOwner()
{
	return RegionOwner;
}

const TArray<ARegion*>& ARegion::GetBorderingRegions()
{
	return BorderingRegions;
}

void ARegion::DeployUnits(int32 unitsAmount)
{
	UnitsInRegion += unitsAmount;
}

void ARegion::DecreaseUnitCount(int32 unitsRemoved)
{
	int value = UnitsInRegion - unitsRemoved;
	UnitsInRegion = FMath::Max(value, 0);
}

void ARegion::ChangeOwnerShip(ACharacter* newOwner, int32 unitsAmount)
{
	RegionOwner = newOwner;
	UnitsInRegion = unitsAmount;
}

