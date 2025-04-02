#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Containers/Map.h"
#include "AiCharacter.generated.h"

class ARegion;

UCLASS()
class RISKY_API AAiCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	int64 TickTime = 0;
	int64 TockTime = 0;

	void tick();

	double tock();

	ARegion* GetRegionWithBorderingEnemy();

	void WriteStatsIntoFile();

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

	TArray<TPair<ARegion*, double>> GetTopResults(TMap<ARegion*, double> map);

	TArray<TPair<ARegion*, double>> GetRegionsMostUnits();

	void InitMap();

	void InitAttackMap(ARegion* region);

	void DeployUnits(int32 unitsToDeploy);

	void EvaluateRegionForAttacking(ARegion* region);

	bool AttackValuableRegion(ARegion* ownRegion, ARegion* regionToAttack);

	void FilterRegionWithNoPoints(TMap<ARegion*, double> map);

public:

	class UAiStats* Statistic;

	AAiCharacter();

	void StartDeploymentPhase() override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;

	void FilterForDeployment();

	void PredictDeployment();

	void PredictFortification(ARegion* regionToTransfer);

	int32 MinimaxFortification(int32 depth, bool isMaximizing);

	int32 MinimaxDeployment(int32 depth, bool isMaximizing, bool firstIteration = false);

	int32 EvaluateGameState();

};
