// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class ATurnManager;
class ARegion;
class UCharacterCard;
struct FCard;

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

	UPROPERTY()
	UCharacterCard* CharacterCard;

	void virtual ConsumeCards(FCard* card1, FCard* card2, FCard* card3);

	void virtual AddCard();

public:	
	ATurnManager* TurnManager;

	virtual void FinishedCurrentPhase();

	virtual void StartDeploymentPhase();

	virtual void StartAttackPhase();

	virtual void StartFortificationPhase();

	void TransferUnits(ARegion* originRegion, ARegion* destinationRegion, int32 units);

	struct FAttackResults* GetDiceResults(ARegion* enemyRegion, int32 attackingUnits);

	void ExecuteAttack(ARegion* ownRegion, ARegion* enemyRegion, FAttackResults* results);

	virtual void TurnManagerRef(ATurnManager* tManager);

	virtual void IsCharacterDead();

	ABaseCharacter();

	TArray<ARegion*> RegionsOwned;

	UPROPERTY(EditAnywhere)
	FColor ColorIdentity;

	bool CharacterDead = false;
};
