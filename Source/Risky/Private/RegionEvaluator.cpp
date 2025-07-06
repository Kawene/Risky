// Fill out your copyright notice in the Description page of Project Settings.


#include "RegionEvaluator.h"
#include "Region.h"
#include "Province.h"
#include "Character/AiCharacter.h"


URegionEvaluator::URegionEvaluator()
{
	PrioritizedRegions = TMap<ARegion*, double>();
	PrioritizedRegionsToAttack = TMap<ARegion*, double>();
}

void URegionEvaluator::FilterForDeployment(EAiDifficulty aiDifficulty)
{
	InitMap();

	FilterSafeRegion();

	if (aiDifficulty != EAiDifficulty::Easy)
	{
		PrioritizeCloseRegions();

		PrioritizePopulatedRegions();

		PrioritizeProvince();
	}
}

ARegion* URegionEvaluator::GetRegionToTransferForFortification()
{
	InitMap();

	FilterDangerousRegion();

	FilterRegionWithLowPopulation(1);
	if (!PrioritizedRegions.IsEmpty())
	{
		PrioritizePopulatedRegions();

		ARegion* regionToTransferWith = GetTopResults(EMapType::Own)[0].Key;

		return regionToTransferWith;
	}

	return nullptr;
}

void URegionEvaluator::FilterForFortification(ARegion* connectedRegion)
{
	InitMapWihoutSafeRegion();

	FilterConnectedRegion(connectedRegion);
}

bool URegionEvaluator::IsEmpty()
{
	return PrioritizedRegions.IsEmpty();
}

void URegionEvaluator::InitMapWihoutSafeRegion()
{
	InitMap();

	FilterSafeRegion();
}

void URegionEvaluator::InitMapForAttackingRegion(ARegion* region)
{
	InitAttackMap(region);

	EvaluateRegionForAttacking(region);
}


void URegionEvaluator::PrioritizeCloseRegions()
{
	for (TPair<ARegion*, double>& pair : PrioritizedRegions)
	{
		TSet<ARegion*> visited;
		CheckCloseRegions(pair, pair.Key, visited, 0);
	}
}

void URegionEvaluator::PrioritizePopulatedRegions()
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

void URegionEvaluator::PrioritizeProvince()
{
	TMap<AProvince*, double> prioritizedProvince;

	for (auto pair : PrioritizedRegions)
	{
		if (!prioritizedProvince.Contains(pair.Key->GetProvince()))
		{
			prioritizedProvince.Add(pair.Key->GetProvince(), 0);
		}
	}

	for (auto region : Ai->RegionsOwned)
	{
		if (prioritizedProvince.Contains(region->GetProvince()))
		{
			prioritizedProvince[region->GetProvince()]++;
		}
	}

	for (TPair<ARegion*, double>& pair : PrioritizedRegions)
	{
		pair.Value += prioritizedProvince[pair.Key->GetProvince()];

		if (prioritizedProvince[pair.Key->GetProvince()] > 2)
		{
			for (ARegion* neighbours : pair.Key->GetBorderingRegions())
			{
				if (neighbours->GetRegionOwner() != Ai && neighbours->GetProvince() == pair.Key->GetProvince())
				{
					pair.Value += 4;
				}
			}
		}
	}
}

void URegionEvaluator::CheckCloseRegions(TPair<ARegion*, double>& pair, ARegion* currentRegion, TSet<ARegion*>& visited, int32 iteration)
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

		if (neighbor->GetRegionOwner() == Ai)
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

void URegionEvaluator::FilterSafeRegion()
{
	auto hasEnemyNeihbors = ([this](const TPair<ARegion*, double>& pair) -> bool
		{
			for (ARegion* neighbor : pair.Key->GetBorderingRegions())
			{
				if (neighbor->GetRegionOwner() != Ai)
				{
					return true;
				}
			}
			return false;
		});

	PrioritizedRegions = PrioritizedRegions.FilterByPredicate(hasEnemyNeihbors);
}

void URegionEvaluator::FilterDangerousRegion()
{
	auto hasEnemyNeihbors = ([this](const TPair<ARegion*, double>& pair) -> bool
		{
			for (ARegion* neighbor : pair.Key->GetBorderingRegions())
			{
				if (neighbor->GetRegionOwner() != Ai)
				{
					return false;
				}
			}
			return true;
		});

	PrioritizedRegions = PrioritizedRegions.FilterByPredicate(hasEnemyNeihbors);
}

void URegionEvaluator::FilterRegionWithLowPopulation(int32 min)
{
	auto hasEnoughUnits = ([min](const TPair<ARegion*, double>& pair) -> bool
		{
			return pair.Key->GetUnits() > min;
		});

	PrioritizedRegions = PrioritizedRegions.FilterByPredicate(hasEnoughUnits);
}

void URegionEvaluator::FilterConnectedRegion(ARegion* region)
{
	auto hasEnoughUnits = ([region](const TPair<ARegion*, double>& pair) -> bool
		{
			return region->CanFortifyThisRegion(pair.Key);
		});

	PrioritizedRegions = PrioritizedRegions.FilterByPredicate(hasEnoughUnits);
}

TArray<TPair<ARegion*, double>> URegionEvaluator::GetTopResults(EMapType mapType)
{
	TMap<ARegion*, double> map;
	switch (mapType)
	{
	case EMapType::Own:
		map = PrioritizedRegions;
		break;
	case EMapType::Enemy:
		map = PrioritizedRegionsToAttack;
		break;
	}

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

TArray<TPair<ARegion*, double>> URegionEvaluator::GetRegionsMostUnits()
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

int32 URegionEvaluator::PrioritizedNum()
{
	return PrioritizedRegions.Num();
}

void URegionEvaluator::AddRegionToMap(ARegion* region)
{
	PrioritizedRegions.Add(region, 0);
}

void URegionEvaluator::InitMap()
{
	PrioritizedRegions = TMap<ARegion*, double>();

	if (!Ai)
	{
		return;
	}

	for (ARegion* region : Ai->RegionsOwned)
	{
		PrioritizedRegions.Add(region, 0);
	}
}

void URegionEvaluator::InitAttackMap(ARegion* region)
{
	PrioritizedRegionsToAttack = TMap<ARegion*, double>();
	for (ARegion* neighbours : region->GetBorderingRegions())
	{
		if (Ai != neighbours->GetRegionOwner())
		{
			PrioritizedRegionsToAttack.Add(neighbours, 0);
		}
	}
}


void URegionEvaluator::EvaluateRegionForAttacking(ARegion* region)
{
	int32 units = region->GetUnits();

	for (TPair<ARegion*, double>& neighboursPair : PrioritizedRegionsToAttack)
	{

		ARegion* neighboursRegion = neighboursPair.Key;
		int32 neighboursUnits = neighboursRegion->GetUnits();

		//Prioritize low population region
		if (neighboursUnits < units)
		{
			int32 diff = units - neighboursUnits;
			neighboursPair.Value += diff;
		}
		else
		{
			for (TPair<ARegion*, double>& tempPair : PrioritizedRegionsToAttack)
			{
				tempPair.Value -= 2;
			}
		}

		//Prioritize lonely region
		for (ARegion* neighboursOfNeighbours : neighboursRegion->GetBorderingRegions())
		{
			neighboursPair.Value -= 0.5;
			if (Ai == neighboursOfNeighbours->GetRegionOwner())
			{
				neighboursPair.Value += 3;
			}
			else if (neighboursOfNeighbours->GetRegionOwner() != neighboursRegion->GetRegionOwner())
			{
				neighboursPair.Value += 1;
			}
		}

		if (neighboursRegion->GetProvince() == region->GetProvince())
		{
			neighboursPair.Value += 3;
		}
		else if (neighboursRegion->GetProvince()->HasControlOverProvince(neighboursRegion->GetRegionOwner())) {
			neighboursPair.Value += 5;
		}
	}
}