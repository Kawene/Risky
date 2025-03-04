// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AiStats.generated.h"

UCLASS()
class RISKY_API UAiStats: public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	double TimeDeployment;

	UPROPERTY()
	double TimeAttack;

	UPROPERTY()
	double TimeFortification;
};