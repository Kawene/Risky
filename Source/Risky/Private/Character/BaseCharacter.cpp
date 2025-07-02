// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Manager/TurnManager.h"
#include "Region.h"
#include "Math/UnrealMathUtility.h"
#include "AttackResults.h"


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool ABaseCharacter::CombatRegion(ARegion* ownRegion, ARegion* enemyRegion, int32 attackingUnits)
{
	if (TurnManager->InSimulation)
	{
		ownRegion->DecreaseUnitCount(enemyRegion->GetUnits());
		enemyRegion->ChangeOwnerShip(ownRegion->GetRegionOwner(), 0);
		return true;
	}
	else {
		CombatRoll(ownRegion, enemyRegion, attackingUnits);
		if (enemyRegion->GetUnits() == 0)
		{
			enemyRegion->ChangeOwnerShip(ownRegion->GetRegionOwner(), 0);
			return true;
		}
		return false;
	}
}

void ABaseCharacter::CombatRoll(ARegion* ownRegion, ARegion* enemyRegion, int32 attackingUnits)
{
	ExecuteAttack(ownRegion, enemyRegion, GetDiceResults(enemyRegion, attackingUnits));
}

void ABaseCharacter::FinishedCurrentPhase()
{
	TurnManager->ProceedToNextPhase();
}

void ABaseCharacter::StartDeploymentPhase()
{
}

void ABaseCharacter::StartAttackPhase()
{
}

void ABaseCharacter::StartFortificationPhase()
{
}

void ABaseCharacter::TransferUnits(ARegion* originRegion, ARegion* destinationRegion, int32 units)
{
	if (originRegion->GetRegionOwner() == destinationRegion->GetRegionOwner())
	{
		originRegion->DecreaseUnitCount(units);
		destinationRegion->DeployUnits(units);
	}
}

FAttackResults* ABaseCharacter::GetDiceResults(ARegion* enemyRegion, int32 attackingUnits)
{
	TArray<int32> attackingDice;
	attackingUnits = FMath::Min(3, attackingUnits);
	attackingDice.Reserve(attackingUnits);
	for (size_t i = 0; i < attackingUnits; i++)
	{
		attackingDice.Add(FMath::RandRange(1, 6));
	}
	attackingDice.Sort();

	TArray<int32> defendingDice;
	int32 defenders = FMath::Min(2, enemyRegion->GetUnits());
	defendingDice.Reserve(defenders);
	for (size_t i = 0; i < defenders; i++)
	{
		defendingDice.Add(FMath::RandRange(1, 6));
	}
	defendingDice.Sort();

	FAttackResults* attackResults = new FAttackResults();

	if (attackingDice.Num() > 0) attackResults->AttackResult1 = attackingDice.Last();
	if (attackingDice.Num() > 1) attackResults->AttackResult2 = attackingDice[attackingDice.Num() - 2];
	if (attackingDice.Num() > 2) attackResults->AttackResult3 = attackingDice[attackingDice.Num() - 3];

	if (defendingDice.Num() > 0) attackResults->DefenceResult1 = defendingDice.Last();
	if (defendingDice.Num() > 1) attackResults->DefenceResult2 = defendingDice[defendingDice.Num() - 2];

	return attackResults;
}

void ABaseCharacter::ExecuteAttack(ARegion* ownRegion, ARegion* enemyRegion, FAttackResults* results)
{
	if (results->AttackResult1 > results->DefenceResult1)
	{
		enemyRegion->DecreaseUnitCount(1);
	}
	else 
	{
		ownRegion->DecreaseUnitCount(1);
	}

	if (results->AttackResult2 != 0 && results->DefenceResult2 != 0)
	{
		if (results->AttackResult2 > results->DefenceResult2)
		{
			enemyRegion->DecreaseUnitCount(1);
		}
		else
		{
			ownRegion->DecreaseUnitCount(1);
		}
	}
}

void ABaseCharacter::TurnManagerRef(ATurnManager* tManager)
{
	TurnManager = tManager;
}

void ABaseCharacter::IsCharacterDead()
{
	if (RegionsOwned.IsEmpty() && !TurnManager->InSimulation)
	{
		CharacterDead = true;
		TurnManager->CharacterDied(this);
	}
}

