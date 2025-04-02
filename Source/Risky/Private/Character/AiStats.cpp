// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiStats.h"



double UAiStats::TicTok()
{
	return (TockTime - TickTime) * FPlatformTime::GetSecondsPerCycle() * 1000.0f;
}

void UAiStats::Tick()
{
	TickTime = FPlatformTime::Cycles();
}

void UAiStats::TockDeployment()
{
	TockTime = FPlatformTime::Cycles();
	TimeDeployment = TicTok();
}

void UAiStats::TockAttack()
{
	TockTime = FPlatformTime::Cycles();
	TimeAttack = TicTok();
}

void UAiStats::TockFortification()
{
	TockTime = FPlatformTime::Cycles();
	TimeFortification = TicTok();
}

void UAiStats::WriteStatsIntoFile(double& total)
{
	FString message;
	message += "Stats for:" + this->GetFName().ToString() + "\n";

	message += FString::Printf(TEXT("Time Deployment =\t %f\n"), TimeDeployment);

	message += FString::Printf(TEXT("Time Attack =\t\t %f\n"), TimeAttack);

	message += FString::Printf(TEXT("Time Fortification =\t %f\n"), TimeFortification);

	double totalTime = TimeDeployment + TimeAttack + TimeFortification;

	message += FString::Printf(TEXT("Time Total =\t\t %f\n\n"), totalTime);

	FString filePath = FPaths::ProjectDir() + TEXT("StatsAI.txt");

	FFileHelper::SaveStringToFile(
		message,
		*filePath,
		FFileHelper::EEncodingOptions::AutoDetect,
		&IFileManager::Get(),
		FILEWRITE_Append
	);

	total += totalTime;
}
