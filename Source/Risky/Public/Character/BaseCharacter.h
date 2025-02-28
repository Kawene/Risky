// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class ATurnManager;

UCLASS()
class RISKY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ATurnManager* TurnManager;

public:	
	virtual void FinishedCurrentPhase();

	virtual void StartDeploymentPhase(int32 unitsToDeploy);

	virtual void StartAttackPhase();

	virtual void StartFortificationPhase();

	void TurnManagerRef(ATurnManager* tManager);

	TArray<class ARegion*> RegionsOwned;

	int32 CurrentUnitsToDeploy;

};
