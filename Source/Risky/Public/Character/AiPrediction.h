// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AiPrediction.generated.h"


UCLASS()
class RISKY_API UAiPrediction : public UObject
{
	GENERATED_BODY()

	int32 MinimaxFortification(int32 depth, bool isMaximizing);

	int32 MinimaxDeployment(int32 depth, bool isMaximizing, bool firstIteration = false);

	int32 EvaluateGameState();

public:
	UPROPERTY()
	class AAiCharacter* Ai;

	void PredictDeployment(EAiDifficulty aiDifficulty);

	void PredictFortification(class ARegion* regionToTransfer, EAiDifficulty aiDifficulty);
};
