// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RegionEvaluator.generated.h"

class ARegion;

UENUM(BlueprintType)
enum class EMapType : uint8 {
	Own,
	Enemy
};

UCLASS()
class RISKY_API URegionEvaluator : public UObject
{
	GENERATED_BODY()

	TMap<ARegion*, double> PrioritizedRegions;

	TMap<ARegion*, double> PrioritizedRegionsToAttack;

	void PrioritizeCloseRegions();

	void PrioritizePopulatedRegions();

	void PrioritizeProvince();

	void CheckCloseRegions(TPair<ARegion*, double>& pair, ARegion* currentRegion, TSet<ARegion*>& visited, int32 iteration);

	void FilterSafeRegion();

	void FilterDangerousRegion();

	void FilterRegionWithLowPopulation(int32 min);

	void FilterConnectedRegion(ARegion* region);

	void InitMap();

	void InitAttackMap(ARegion* region);

	void EvaluateRegionForAttacking(ARegion* region);

	void FilterRegionWithNoPoints(TMap<ARegion*, double> map);


public:
	class AAiCharacter* Ai;
	
	void FilterForDeployment();

	ARegion* GetRegionToTransferForFortification();

	void FilterForFortification(ARegion* connectedRegion);

	bool IsEmpty();

	void InitMapWihoutSafeRegion();

	void InitMapForAttackingRegion(ARegion* region);

	TArray<TPair<ARegion*, double>> GetTopResults(EMapType mapType);

	TArray<TPair<ARegion*, double>> GetRegionsMostUnits();

	int32 PrioritizedNum();

	void AddRegionToMap(ARegion* region);
	
};
