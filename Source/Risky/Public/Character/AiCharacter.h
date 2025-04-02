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

	void DeployUnits(int32 unitsToDeploy);

	bool AttackValuableRegion(ARegion* ownRegion, ARegion* regionToAttack);

	class UAiStats* Statistic;

	class UAiPrediction* Prediction;

public:

	class URegionEvaluator* RegionEvaluator;

	AAiCharacter();

	void StartDeploymentPhase() override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;
};
