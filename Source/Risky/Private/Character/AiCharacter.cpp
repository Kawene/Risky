// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiCharacter.h"
#include "Character/AiStats.h"
#include "Manager/TurnManager.h"
#include "Region.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"


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
	GetRegionWithBorderingEnemy()->DeployUnits(3);
	Statistic->TimeDeployment = tock();
	FinishedCurrentPhase();
}

void AAiCharacter::StartAttackPhase()
{
	tick();
	for (auto ownRegion : RegionsOwned)
	{
		for (auto neighbours : ownRegion->GetBorderingRegions())
		{
			while (ownRegion->CanAttackThisRegion(neighbours))
			{
				if (CombatRegion(ownRegion, neighbours, ownRegion->GetUnits() - 1))
				{
					neighbours->ChangeOwnerShip(this, ownRegion->GetUnits() - 1);
					Statistic->TimeAttack = tock();
					FinishedCurrentPhase();
					return;
				}
			}
		}
	}

	Statistic->TimeAttack = tock();
	FinishedCurrentPhase();
}

void AAiCharacter::StartFortificationPhase()
{
	tick();
	bool noEnemy;
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
	}
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

void AAiCharacter::tick()
{
	TickTime = FPlatformTime::Cycles();  // Capture cycles at the start
}

double AAiCharacter::tock()
{
	TockTime = FPlatformTime::Cycles();  // Capture cycles at the end
	return (TockTime - TickTime) * FPlatformTime::GetSecondsPerCycle() * 1000.0f; // Return time in ms
}
