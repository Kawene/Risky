// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiCharacter.h"
#include "Region.h"
#include "Math/UnrealMathUtility.h"
#include "Character/AiStats.h"
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
	FinishedCurrentPhase();
	Statistic->TimeDeployment = tock();
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
	message += "Stats for AI number" + this->GetFName().ToString() + "\n";

	message += FString::Printf(TEXT("Time Deployment = %f\n"), Statistic->TimeDeployment); 

	message += FString::Printf(TEXT("Time Attack = %f\n"), Statistic->TimeAttack);

	message += FString::Printf(TEXT("Time Fortification = %f\n"), Statistic->TimeFortification);

	message += FString::Printf(TEXT("Time Total = %f\n\n\n"), (Statistic->TimeDeployment + Statistic->TimeAttack + Statistic->TimeFortification));

	FString filePath = FPaths::ProjectDir() + TEXT("StatsAI.txt");

	FFileHelper::SaveStringToFile(
		message,
		*filePath,
		FFileHelper::EEncodingOptions::AutoDetect,
		&IFileManager::Get(),
		FILEWRITE_Append
	);
}

void AAiCharacter::tick()
{
	TickTime = FPlatformTime::Seconds();
}

double AAiCharacter::tock()
{
	TockTime = FPlatformTime::Seconds();
	return (TockTime - TickTime) * 1000.f;
}
