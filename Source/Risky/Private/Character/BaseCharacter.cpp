// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Manager/TurnManager.h"
#include "Region.h"
#include "Math/UnrealMathUtility.h"

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
	TArray<int32> attackingDice;
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

	int32 maxIteration = FMath::Min(defenders, attackingUnits) - 1;

	for (auto dice : attackingDice)
	{
		FString Message = FString::Format(TEXT("Attacking: {0}"), { dice });
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message);
	}
	for (auto dice : defendingDice)
	{
		FString Message = FString::Format(TEXT("Defending: {0}"), { dice });
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message);
	}
	for (int32 i = 0; i <= maxIteration; ++i)
	{
		FString Message = FString::Format(TEXT("AttackingDice: {0} DefendingDice: {1}"), { attackingDice[attackingDice.Num() - 1 - i], defendingDice[defendingDice.Num() - 1 - i] });
		if (attackingDice[attackingDice.Num() - 1 - i] > defendingDice[defendingDice.Num() - 1 - i])
		{
			enemyRegion->DecreaseUnitCount(1);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
		}
		else {
			ownRegion->DecreaseUnitCount(1);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);
		}
	}
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

void ABaseCharacter::TurnManagerRef(ATurnManager* tManager)
{
	TurnManager = tManager;
}

void ABaseCharacter::IsCharacterDead()
{
	if (RegionsOwned.IsEmpty() && !TurnManager->InSimulation)
	{
		TurnManager->CharacterDied(this);
		Destroy();
	}
}

