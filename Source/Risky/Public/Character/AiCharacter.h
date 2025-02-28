// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AiCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API AAiCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AAiCharacter();

	void StartDeploymentPhase(int32 unitsToDeploy) override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;
	
};
