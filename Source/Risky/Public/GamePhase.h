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
	NoStop,
	ByTurn,
	ByPhases
};