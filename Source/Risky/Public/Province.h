// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Province.generated.h"

class ARegion;

class ABaseCharacter;

UCLASS()
class RISKY_API AProvince : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<ARegion*> Regions;

	UPROPERTY(EditAnywhere)
	int32 Bonus;
	
public:
	int32 GetBonusIfOwner(ABaseCharacter* character);

	bool HasControlOverProvince(ABaseCharacter* character);

	bool IsRegionInProvince(ARegion* region);
};
