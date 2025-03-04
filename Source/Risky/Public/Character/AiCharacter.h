#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AiCharacter.generated.h"

UCLASS()
class RISKY_API AAiCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	int64 TickTime = 0;
	int64 TockTime = 0;

	void tick();

	double tock();

	class ARegion* GetRegionWithBorderingEnemy();

	void WriteStatsIntoFile();

public:

	class UAiStats* Statistic;
	AAiCharacter();

	void StartDeploymentPhase(int32 unitsToDeploy) override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;	
};
