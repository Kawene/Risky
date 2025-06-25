#pragma once

UENUM(BlueprintType)
enum class EGamePhase : uint8 {
	DeploymentPhase,
	AttackPhase,
	FortificationPhase,
	NotCurrentTurn
};

UENUM(BlueprintType)
enum class EAiPhasesSteps : uint8 {
	NoStop = 0,
	ByTurn = 1,
	ByPhases = 2
};