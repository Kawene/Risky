#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Containers/Map.h"
#include "AiCharacter.generated.h"

class ARegion;

UENUM(BlueprintType)
enum class EAiDifficulty : uint8 {
	Easy = 0,
	Medium = 1,
	Hard = 2
};

UCLASS()
class RISKY_API AAiCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	void DeployUnits(int32 unitsToDeploy);

	bool AttackValuableRegion(ARegion* ownRegion, ARegion* regionToAttack);

	UPROPERTY()
	class UAiStats* Statistic;
	
	UPROPERTY()
	class UAiPrediction* Prediction;

public:

	UPROPERTY()
	class URegionEvaluator* RegionEvaluator;

	AAiCharacter();

	void StartDeploymentPhase() override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;

protected:
	virtual void AddCard() override;
};
