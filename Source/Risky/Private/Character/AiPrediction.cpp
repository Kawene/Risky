// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiPrediction.h"
#include "Region.h"
#include "Province.h"
#include "Character/BaseCharacter.h"
#include "Character/AiCharacter.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "RegionEvaluator.h"
#include "Manager/TurnManager.h"


struct FGameStateSnapshot
{
	TMap<ARegion*, TPair<ABaseCharacter*, int32>> RegionInfo;

	FGameStateSnapshot()
	{
		RegionInfo = TMap<ARegion*, TPair<ABaseCharacter*, int32>>();
	}

	void SaveState(UWorld* world)
	{
		RegionInfo = TMap<ARegion*, TPair<ABaseCharacter*, int32>>();

		TArray<AActor*> allRegions {};
		UGameplayStatics::GetAllActorsOfClass(world, ARegion::StaticClass(), allRegions);

		for (AActor* actor : allRegions)
		{
			ARegion* region = StaticCast<ARegion*>(actor);
			RegionInfo.Add(region, { region->GetRegionOwner(), region->GetUnits() });
		}
	}

	void RestoreState()
	{
		for (auto& pair : RegionInfo)
		{
			pair.Key->ChangeOwnerShip(pair.Value.Key, pair.Value.Value);
		}

	}
};


void UAiPrediction::PredictDeployment()
{
	FGameStateSnapshot snapshot {};
	snapshot.SaveState(GetWorld());

	ARegion* bestRegion = nullptr;
	int32 bestScore = INT_MIN;

	auto bestList = Ai->RegionEvaluator->GetTopResults(EMapType::Own);

	int32 regionToPredict = FMath::Min(5, bestList.Num());

	for (size_t i = 0; i < regionToPredict; i++)
	{
		ARegion* region = bestList[i].Key;

		region->DeployUnits(Ai->TurnManager->GetsNumberOfUnitsToDeploy(Ai));

		int32 predictedScore = MinimaxDeployment(3, true, true);

		snapshot.RestoreState();

		if (predictedScore > bestScore)
		{
			bestScore = predictedScore;
			bestRegion = region;
		}
	}

	if (bestRegion)
	{
		bestRegion->DeployUnits(Ai->TurnManager->GetsNumberOfUnitsToDeploy(Ai));
	}
}

void UAiPrediction::PredictFortification(ARegion* regionToTransfer)
{
	FGameStateSnapshot snapshot;
	snapshot.SaveState(GetWorld());

	ARegion* bestRegion = nullptr;
	int32 bestScore = INT_MIN;

	auto bestList = Ai->RegionEvaluator->GetTopResults(EMapType::Own);

	for (size_t i = 0; i < bestList.Num(); i++)
	{
		ARegion* region = bestList[i].Key;

		Ai->TransferUnits(regionToTransfer, region, regionToTransfer->GetUnits() - 1);

		int32 predictedScore = MinimaxFortification(3, false);

		snapshot.RestoreState();

		if (predictedScore > bestScore)
		{
			bestScore = predictedScore;
			bestRegion = region;
		}
	}

	if (bestRegion)
	{
		Ai->TransferUnits(regionToTransfer, bestRegion, regionToTransfer->GetUnits() - 1);
	}
}

int32 UAiPrediction::MinimaxFortification(int32 depth, bool isMaximizing)
{
	if (depth == 0)
	{
		return EvaluateGameState();
	}

	if (isMaximizing)
	{
		//Depth 2, 4, 6, 8...
		Ai->StartDeploymentPhase();
		Ai->StartAttackPhase();
		Ai->StartFortificationPhase();

		int32 score = MinimaxDeployment(depth - 1, false);

		return score;
	}
	else {
		//Depth 1, 3, 5, 7...
		int32 worstScore = INT_MAX;

		for (ABaseCharacter* character : Ai->TurnManager->GetTurnOrderFrom(Ai))
		{
			if (!character->RegionsOwned.IsEmpty())
			{
				AAiCharacter* otherAi = Cast<AAiCharacter>(character);

				otherAi->StartDeploymentPhase();

				otherAi->StartAttackPhase();

				otherAi->StartFortificationPhase();
			}
		}
		return MinimaxDeployment(depth - 1, true);
	}
}

int32 UAiPrediction::MinimaxDeployment(int32 depth, bool isMaximizing, bool firstIteration)
{

	if (depth == 0)
	{
		return EvaluateGameState();
	}

	if (isMaximizing)
	{
		int32 bestScore = INT_MIN;

		if (firstIteration)
		{
			//Depth 1
			Ai->StartAttackPhase();
			Ai->StartFortificationPhase();

			int32 score = MinimaxDeployment(depth - 1, false);

			bestScore = FMath::Max(score, bestScore);
		}
		else {

			//Depth 3, 5, 7, 9...
			Ai->RegionEvaluator->FilterForDeployment();
			auto bestList = Ai->RegionEvaluator->GetTopResults(EMapType::Own);


			for (auto pair : bestList)
			{
				FGameStateSnapshot snapshot;
				snapshot.SaveState(GetWorld());

				ARegion* region = pair.Key;

				region->DeployUnits(Ai->TurnManager->GetsNumberOfUnitsToDeploy(Ai));

				Ai->StartAttackPhase();
				Ai->StartFortificationPhase();

				int32 score = MinimaxDeployment(depth - 1, false);

				bestScore = FMath::Max(score, bestScore);


				snapshot.RestoreState();
			}
		}
		return bestScore;
	}
	else {
		//Depth 2, 4, 6, 8...
		int32 worstScore = INT_MAX;

		for (ABaseCharacter* character : Ai->TurnManager->GetTurnOrderFrom(Ai))
		{
			if (!character->RegionsOwned.IsEmpty())
			{
				AAiCharacter* otherAi = Cast<AAiCharacter>(character);

				otherAi->StartDeploymentPhase();

				otherAi->StartAttackPhase();

				otherAi->StartFortificationPhase();
			}
		}
		return MinimaxDeployment(depth - 1, true);
	}
}

int32 UAiPrediction::EvaluateGameState()
{
	int32 totalPoints = 0;

	TMap<AProvince*, double> prioritizedProvince;

	for (ARegion* region : Ai->RegionsOwned)
	{
		if (!prioritizedProvince.Contains(region->GetProvince()))
		{
			prioritizedProvince.Add(region->GetProvince(), 0);
		}
	}

	for (auto region : Ai->RegionsOwned)
	{
		if (prioritizedProvince.Contains(region->GetProvince()))
		{
			prioritizedProvince[region->GetProvince()]++;
		}
	}

	for (ARegion* region : Ai->RegionsOwned)
	{
		totalPoints += 3 * prioritizedProvince[region->GetProvince()];
		totalPoints += region->GetUnits() * prioritizedProvince[region->GetProvince()];
	}

	for (AProvince* province : Ai->TurnManager->Provinces)
	{
		if (province->SomeoneHasControl())
		{
			if (province->HasControlOverProvince(Ai))
			{
				totalPoints += 30;
			}
			else {
				for (ABaseCharacter* character : Ai->TurnManager->Characters)
				{
					if (character != Ai && province->HasControlOverProvince(character))
					{
						totalPoints -= 20;
					}
				}
			}
		}
	}


	for (size_t i = 0; i < Ai->TurnManager->Characters.Num(); ++i)
	{
		if (i == 0)
		{
			if (StaticCast<APlayerCharacter*>(Ai->TurnManager->Characters[i])->AiPlayer->RegionsOwned.IsEmpty())
			{
				totalPoints += 50;
			}
		}
		else if (Ai->TurnManager->Characters[i]->RegionsOwned.IsEmpty()) {
			totalPoints += 50;
		}
	}

	return totalPoints;
}