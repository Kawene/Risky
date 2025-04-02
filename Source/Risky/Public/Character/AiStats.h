// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AiStats.generated.h"

UCLASS()
class RISKY_API UAiStats: public UObject
{
	GENERATED_BODY()

	int64 TickTime = 0;
	int64 TockTime = 0;

	double TimeDeployment;

	double TimeAttack;

	double TimeFortification;

	double TicTok();

public:

	void Tick();

	void TockDeployment();

	void TockAttack();

	void TockFortification();

	void WriteStatsIntoFile(double& total);
};