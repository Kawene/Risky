// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiCharacter.h"
#include "Character/AiStats.h"
#include "Manager/TurnManager.h"
#include "Region.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"
#include "Containers/Map.h"


int64 unixTimeNow()
{
	FDateTime timeUtc = FDateTime::UtcNow();
	return timeUtc.ToUnixTimestamp() * 1000 + timeUtc.GetMillisecond();
}

AAiCharacter::AAiCharacter()
{
	Statistic =  CreateDefaultSubobject<UAiStats>(TEXT("Statistic"));
}

void AAiCharacter::StartDeploymentPhase(int32 unitsToDeploy)
{
	tick();

	InitMap();

	FilterSafeRegion();

	PrioritizeCloseRegions();

	PrioritizePopulatedRegions();

	//FilterRegionWithNoPoints(PrioritizedRegions);

	DeployUnits(unitsToDeploy);

	Statistic->TimeDeployment = tock();
	FinishedCurrentPhase();
}

void AAiCharacter::StartAttackPhase()
{
	tick();

	InitMap();

	FilterSafeRegion();

	bool shouldAttack = true;
	int32 index = 0;

	while (shouldAttack && index < PrioritizedRegions.Num())
	{
		auto test = GetRegionsMostUnits();

		auto topPair = GetRegionsMostUnits()[index];

		ARegion* region = topPair.Key;
		if (region->GetUnits() < 4)
		{
			shouldAttack = false;
			break;
		}

		InitAttackMap(region);

		EvaluateRegionForAttacking(region);

		auto sortedPair = GetTopResults(PrioritizedRegionsToAttack);

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

	Statistic->TimeAttack = tock();
	FinishedCurrentPhase();
}

void AAiCharacter::StartFortificationPhase()
{
	tick();
	/*bool noEnemy;
	for (auto ownRegion : RegionsOwned)
	{
		if (ownRegion->GetUnits() < 2)
		{
			continue;
		}

		noEnemy = true;
		for (auto neighbours : ownRegion->GetBorderingRegions())
		{
			if (neighbours->GetRegionOwner() != this)
			{
				noEnemy = false;
			}
		}

		if (noEnemy)
		{
			//Check if connected
			TransferUnits(ownRegion, GetRegionWithBorderingEnemy(), ownRegion->GetUnits() - 1);
			Statistic->TimeFortification = tock();
			WriteStatsIntoFile();
			FinishedCurrentPhase();
			return;
		}
	}*/
	Statistic->TimeFortification = tock();
	WriteStatsIntoFile();
	FinishedCurrentPhase();
}

ARegion* AAiCharacter::GetRegionWithBorderingEnemy()
{
	for (auto ownRegion : RegionsOwned)
	{
		for (auto neighbours : ownRegion->GetBorderingRegions())
		{
			if (neighbours->GetRegionOwner() != this)
			{
				return ownRegion;
			}
		}
	}
	//Should almost never get here unless the game is over
	return nullptr;
}

void AAiCharacter::WriteStatsIntoFile()
{
	FString message;
	message += "Stats for:" + this->GetFName().ToString() + "\n";

	message += FString::Printf(TEXT("Time Deployment =\t %f\n"), Statistic->TimeDeployment); 

	message += FString::Printf(TEXT("Time Attack =\t\t %f\n"), Statistic->TimeAttack);

	message += FString::Printf(TEXT("Time Fortification =\t %f\n"), Statistic->TimeFortification);

	double totalTime = Statistic->TimeDeployment + Statistic->TimeAttack + Statistic->TimeFortification;

	message += FString::Printf(TEXT("Time Total =\t\t %f\n\n"), totalTime);

	FString filePath = FPaths::ProjectDir() + TEXT("StatsAI.txt");

	FFileHelper::SaveStringToFile(
		message,
		*filePath,
		FFileHelper::EEncodingOptions::AutoDetect,
		&IFileManager::Get(),
		FILEWRITE_Append
	);

	TurnManager->TotalAiTimes += totalTime;
}

void AAiCharacter::PrioritizeCloseRegions()
{
	for (TPair<ARegion*, double>& pair : PrioritizedRegions)
	{
		TSet<ARegion*> visited;
		CheckCloseRegions(pair, pair.Key, visited, 0);
	}
}

void AAiCharacter::PrioritizePopulatedRegions()
{
	auto list = GetRegionsMostUnits();
	const int32 TopCount = FMath::Min(3, list.Num());
	if (TopCount > 1 && list[0].Key->GetUnits() > list[1].Key->GetUnits())
	{
		for (size_t i = 0; i < TopCount; ++i)
		{
			PrioritizedRegions[list[i].Key] += 3 - i;
		}
	}
}

void AAiCharacter::CheckCloseRegions(TPair<ARegion*, double>& pair, ARegion* currentRegion, TSet<ARegion*>& visited, int32 iteration)
{
	if (iteration > 2)
	{
		return;
	}
	visited.Add(currentRegion);

	for (ARegion* neighbor : currentRegion->GetBorderingRegions())
	{
		if (visited.Contains(neighbor))
		{
			continue;
		}

		if (neighbor->GetRegionOwner() == this)
		{
			if (neighbor->GetBorderingRegions().Contains(pair.Key))
			{
				pair.Value += 2;
			}
			else 
			{
				pair.Value += 1;
			}
		}
		CheckCloseRegions(pair, neighbor, visited, iteration + 1);
	}
}

void AAiCharacter::FilterSafeRegion()
{
	auto hasEnemyNeihbors = ([this](const TPair<ARegion*, double>& pair) -> bool
		{
			for (ARegion* neighbor : pair.Key->GetBorderingRegions())
			{
				if (neighbor->GetRegionOwner() != this)
				{
					return true;
				}
			}
			return false;
		});

	PrioritizedRegions = PrioritizedRegions.FilterByPredicate(hasEnemyNeihbors);
}

TArray<TPair<ARegion*, double>> AAiCharacter::GetTopResults(TMap<ARegion*, double> map)
{

	TArray<TPair<ARegion*, double>> SortedPairs;
	for (const TPair<ARegion*, double>& Pair : map)
	{
		SortedPairs.Add(Pair);
	}

	SortedPairs.Sort([](const TPair<ARegion*, double>& A, const TPair<ARegion*, double>& B)
		{
			return A.Value > B.Value;
		});

	return SortedPairs;

}

TArray<TPair<ARegion*, double>> AAiCharacter::GetRegionsMostUnits()
{
	TArray<TPair<ARegion*, double>> SortedPairs;
	for (const TPair<ARegion*, double>& Pair : PrioritizedRegions)
	{
		SortedPairs.Add(Pair);
	}

	SortedPairs.Sort([](const TPair<ARegion*, double>& A, const TPair<ARegion*, double>& B)
		{
			return A.Key->GetUnits() > B.Key->GetUnits();
		});

	return SortedPairs;
}

void AAiCharacter::InitMap()
{
	PrioritizedRegions.Reset();
	for (ARegion* region : RegionsOwned)
	{
		PrioritizedRegions.Add(region, 0);
	}
}

void AAiCharacter::InitAttackMap(ARegion* region)
{
	PrioritizedRegionsToAttack.Reset();
	for (ARegion* neighbours : region->GetBorderingRegions())
	{
		if (this != neighbours->GetRegionOwner())
		{
			PrioritizedRegionsToAttack.Add(neighbours, 0);
		}
	}
}

void AAiCharacter::DeployUnits(int32 unitsToDeploy)
{
	auto bestList = GetTopResults(PrioritizedRegions);

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

void AAiCharacter::EvaluateRegionForAttacking(ARegion* region)
{
	int32 units = region->GetUnits();

	for (TPair<ARegion*, double> &neighboursPair : PrioritizedRegionsToAttack)
	{
		ARegion* neighboursRegion = neighboursPair.Key;
		int32 neighboursUnits = neighboursRegion->GetUnits();
		if (neighboursUnits < units)
		{
			int32 diff = units - neighboursUnits;
			neighboursPair.Value += diff;
		}
		else
		{
			for (TPair<ARegion*, double> &tempPair : PrioritizedRegionsToAttack)
			{
				tempPair.Value -= 2;
			}
		}


		for (ARegion* neighboursOfNeighbours : neighboursRegion->GetBorderingRegions())
		{
			neighboursPair.Value -= 0.5;
			if (this == neighboursOfNeighbours->GetRegionOwner())
			{
				neighboursPair.Value += 3;
			}
			else if (neighboursOfNeighbours->GetRegionOwner() != neighboursRegion->GetRegionOwner())
			{
				neighboursPair.Value += 1;
			}
		}
	}
}

bool AAiCharacter::AttackValuableRegion(ARegion* ownRegion, ARegion* regionToAttack)
{
	bool result = false;
	while (ownRegion->GetUnits() >= regionToAttack->GetUnits() && !result)
	{
		result = CombatRegion(ownRegion, regionToAttack, ownRegion->GetUnits() - 1);

		if (result)
		{
			PrioritizedRegions.Add(regionToAttack, 0);
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

void AAiCharacter::FilterRegionWithNoPoints(TMap<ARegion*, double> map)
{
	auto hasOwnNeihbors = ([this](const TPair<ARegion*, double>& pair) -> bool
		{
			return pair.Value > 0;
		});

	PrioritizedRegions = PrioritizedRegions.FilterByPredicate(hasOwnNeihbors);
}

void AAiCharacter::tick()
{
	TickTime = FPlatformTime::Cycles();  // Capture cycles at the start
}

double AAiCharacter::tock()
{
	TockTime = FPlatformTime::Cycles();  // Capture cycles at the end
	return (TockTime - TickTime) * FPlatformTime::GetSecondsPerCycle() * 1000.0f; // Return time in ms
}
