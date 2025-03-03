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
	CombatRoll(ownRegion, enemyRegion, attackingUnits);

	if (enemyRegion->GetUnits() == 0)
	{
		enemyRegion->ChangeOwnerShip(ownRegion->GetRegionOwner(), 0);
		return true;
	}
	return false;
}

void ABaseCharacter::CombatRoll(ARegion* ownRegion, ARegion* enemyRegion, int32 attackingUnits)
{
	TArray<int32> attackingDice;
	attackingDice.Init(FMath::RandRange(1, 6), attackingUnits);
	attackingDice.Sort();

	TArray<int32> defendingDice;
	int32 defenders = FMath::Min(2, enemyRegion->GetUnits());
	defendingDice.Init(FMath::RandRange(1, 6), defenders);
	defendingDice.Sort();

	int32 maxIteration = FMath::Min(defenders, attackingUnits) - 1;
	for (int32 i = maxIteration ; i >= 0; --i)
	{
		FString Message = FString::Format(TEXT("AttackingDice: {0} DefendingDice: {1}"), { attackingDice[i], defendingDice[i] });
		if (attackingDice[i] > defendingDice[i])
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

void ABaseCharacter::StartDeploymentPhase(int32 unitsToDeploy)
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
	if (RegionsOwned.IsEmpty())
	{
		TurnManager->CharacterDied(this);
		Destroy();
	}
}

