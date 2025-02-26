#pragma once

UENUM(BlueprintType)
enum class EGamePhase : uint8 {
	DeploymentPhase,
	AttackPhase,
	FortificationPhase,
	NotCurrentTurn
};