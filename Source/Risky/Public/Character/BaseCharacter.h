// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class ATurnManager;
class ARegion;

UCLASS()
class RISKY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CombatRegion(ARegion* ownRegion, ARegion* enemyRegion, int32 attackingUnits);

	void CombatRoll(ARegion* ownRegion, ARegion* enemyRegion, int32 attackingUnits);

	int32 CurrentUnitsToDeploy;

public:	
	ATurnManager* TurnManager;

	virtual void FinishedCurrentPhase();

	virtual void StartDeploymentPhase();

	virtual void StartAttackPhase();

	virtual void StartFortificationPhase();

	void TransferUnits(ARegion* originRegion, ARegion* destinationRegion, int32 units);

	virtual void TurnManagerRef(ATurnManager* tManager);

	virtual void IsCharacterDead();

	TArray<ARegion*> RegionsOwned;

	UPROPERTY(EditAnywhere)
	FColor ColorIdentity;

};
