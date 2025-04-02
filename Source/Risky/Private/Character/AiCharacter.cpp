// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiCharacter.h"
#include "Character/AiStats.h"
#include "Manager/TurnManager.h"
#include "Region.h"
#include "Province.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"
#include "Containers/Map.h"
#include "Manager/TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "RegionEvaluator.h"
#include "Character/AiPrediction.h"

AAiCharacter::AAiCharacter()
{
	Statistic =  CreateDefaultSubobject<UAiStats>(TEXT("Statistic"));
	RegionEvaluator = CreateDefaultSubobject<URegionEvaluator>(TEXT("RegionEvaluator"));
	RegionEvaluator->Ai = this;
	Prediction = CreateDefaultSubobject<UAiPrediction>(TEXT("Prediction"));
	Prediction->Ai = this;
}

void AAiCharacter::StartDeploymentPhase()
{
	Statistic->Tick();

	RegionEvaluator->FilterForDeployment();

	if (!TurnManager->InSimulation)
	{
		TurnManager->InSimulation = true;
		Prediction->PredictDeployment();
		TurnManager->InSimulation = false;
	}
	else {
		DeployUnits(TurnManager->GetsNumberOfUnitsToDeploy(this));
	}

	Statistic->TockDeployment();

	if (TurnManager->AiPhasesSteps != EAiPhasesSteps::ByPhases && !TurnManager->InSimulation)
	{
		FinishedCurrentPhase();
	}
}

void AAiCharacter::StartAttackPhase()
{
	Statistic->Tick();

	RegionEvaluator->InitMapWihoutSafeRegion();

	bool shouldAttack = true;
	int32 index = 0;

	while (shouldAttack && index < RegionEvaluator->PrioritizedNum())
	{
		auto topPair = RegionEvaluator->GetRegionsMostUnits()[index];

		ARegion* region = topPair.Key;
		if (region->GetUnits() < 4)
		{
			shouldAttack = false;
			break;
		}

		RegionEvaluator->InitMapForAttackingRegion(region);

		auto sortedPair = RegionEvaluator->GetTopResults(EMapType::Enemy);

		if (!sortedPair.IsEmpty() && sortedPair[0].Value > 2)
		{
			if (AttackValuableRegion(region, sortedPair[0].Key))
			{
				index = 0;
			}
			else {
				++index;
			}

		}
		else {
			++index;
		}
		
	}

	Statistic->TockAttack();

	if (TurnManager->AiPhasesSteps != EAiPhasesSteps::ByPhases && !TurnManager->InSimulation)
	{
		FinishedCurrentPhase();
	}
}

void AAiCharacter::StartFortificationPhase()
{
	Statistic->Tick();

	ARegion* regionToTransferWith = RegionEvaluator->GetRegionToTransferForFortification();

	if (regionToTransferWith)
	{
		RegionEvaluator->FilterForFortification(regionToTransferWith);

		if (!RegionEvaluator->IsEmpty())
		{
			if (!TurnManager->InSimulation)
			{
				TurnManager->InSimulation = true;
				Prediction->PredictFortification(regionToTransferWith);
				TurnManager->InSimulation = false;
			}
			else {
				int32 random = FMath::RandRange(0, RegionEvaluator->PrioritizedNum() - 1);

				ARegion* regionToFortify = RegionEvaluator->GetTopResults(EMapType::Own)[random].Key;

				TransferUnits(regionToTransferWith, regionToFortify, regionToTransferWith->GetUnits() - 1);
			}

		}
	}

	Statistic->TockFortification();
	if (!TurnManager->InSimulation)
	{
		Statistic->WriteStatsIntoFile(TurnManager->TotalAiTimes);
		if (TurnManager->AiPhasesSteps == EAiPhasesSteps::NoStop)
		{
			FinishedCurrentPhase();
		}
	}

}

void AAiCharacter::DeployUnits(int32 unitsToDeploy)
{
	auto bestList = RegionEvaluator->GetTopResults(EMapType::Own);

	if (unitsToDeploy > 10 && FMath::RandRange(0, 100) > 70)
	{
		double diffValue = bestList[0].Value - bestList[1].Value;
		if (diffValue <= 3)
		{
			double total = bestList[0].Value + bestList[1].Value;
			int32 partForBestRegion = bestList[0].Value * unitsToDeploy / total;
			int32 partForSecondRegion = unitsToDeploy - partForBestRegion;
			bestList[0].Key->DeployUnits(partForBestRegion);
			bestList[1].Key->DeployUnits(partForSecondRegion);
			return;
		}
	}

	bestList[0].Key->DeployUnits(unitsToDeploy);
}


bool AAiCharacter::AttackValuableRegion(ARegion* ownRegion, ARegion* regionToAttack)
{
	bool result = false;
	while (ownRegion->HasEnoughUnits() && ownRegion->GetUnits() >= regionToAttack->GetUnits() && !result)
	{
		result = CombatRegion(ownRegion, regionToAttack, ownRegion->GetUnits() - 1);

		if (result)
		{
			RegionEvaluator->AddRegionToMap(regionToAttack);
			if (ownRegion->GetUnits() <= 4)
			{
				TransferUnits(ownRegion, regionToAttack, ownRegion->GetUnits() - 1);
			}
			else {
				int32 totalUnitIShouldTransfer = ownRegion->GetUnits() - 1;
				for (ARegion* neighbours : ownRegion->GetBorderingRegions())
				{
					if (neighbours->GetRegionOwner() != this && !regionToAttack->GetBorderingRegions().Contains(neighbours))
					{
						totalUnitIShouldTransfer--;
					}
				}

				TransferUnits(ownRegion, regionToAttack, FMath::Max(3, totalUnitIShouldTransfer));
			}
		}
	}

	return result;
}
