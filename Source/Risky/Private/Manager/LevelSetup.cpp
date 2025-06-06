// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/LevelSetup.h"
#include "Character/BaseCharacter.h"
#include "Character/AiCharacter.h"
#include "Character/PlayerCharacter.h"
#include "Region.h"
#include "Manager/TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/KismetMathLibrary.h"
#include <GI_LevelData.h>

FVector RGBToLab(const FLinearColor& Color)
{
	float X = 0.4124564f * Color.R + 0.3575761f * Color.G + 0.1804375f * Color.B;
	float Y = 0.2126729f * Color.R + 0.7151522f * Color.G + 0.0721750f * Color.B;
	float Z = 0.0193339f * Color.R + 0.1191920f * Color.G + 0.9503041f * Color.B;

	X = X > 0.008856f ? pow(X, 1.0f / 3.0f) : (7.787f * X) + (16.0f / 116.0f);
	Y = Y > 0.008856f ? pow(Y, 1.0f / 3.0f) : (7.787f * Y) + (16.0f / 116.0f);
	Z = Z > 0.008856f ? pow(Z, 1.0f / 3.0f) : (7.787f * Z) + (16.0f / 116.0f);

	float L = (116.0f * Y) - 16.0f;
	float A = 500.0f * (X - Y);
	float B = 200.0f * (Y - Z);

	return FVector(L, A, B);
}


float ColorDistance(const FLinearColor& A, const FLinearColor& B)
{
	FVector LabA = RGBToLab(A);
	FVector LabB = RGBToLab(B);

	return FMath::Sqrt(FMath::Pow(LabA.X - LabB.X, 2) +
		FMath::Pow(LabA.Y - LabB.Y, 2) +
		FMath::Pow(LabA.Z - LabB.Z, 2));
}

float GetBalancedHue()
{
	int ColorCategory = FMath::RandRange(0, 5);
	switch (ColorCategory)
	{
	case 0: return FMath::FRandRange(0.0f, 30.0f);    // Red-Orange
	case 1: return FMath::FRandRange(30.0f, 60.0f);   // Orange-Yellow
	case 2: return FMath::FRandRange(60.0f, 150.0f);  // Yellow-Green
	case 3: return FMath::FRandRange(150.0f, 210.0f); // Green-Cyan
	case 4: return FMath::FRandRange(210.0f, 270.0f); // Blue
	case 5: return FMath::FRandRange(270.0f, 330.0f); // Purple-Pink
	default: return FMath::FRandRange(0.0f, 360.0f);  // Fallback
	}
}


FLinearColor GetRandomDistinctColor(const TArray<FLinearColor>& ExistingColors, float MinDistance = 25.0f)
{
	const int MaxAttempts = 100;
	FLinearColor BestColor = FLinearColor::White;
	float BestMinDist = 0.0f;

	for (int i = 0; i < MaxAttempts; i++)
	{
		float Hue = GetBalancedHue();
		float Saturation = FMath::FRandRange(0.8f, 1.0f);
		float Value = FMath::FRandRange(0.0f, 1.0f);
		FLinearColor NewColor = UKismetMathLibrary::HSVToRGB(Hue, Saturation, Value);

		float MinDist = FLT_MAX;
		for (const FLinearColor& Color : ExistingColors)
		{
			float Dist = ColorDistance(NewColor, Color);
			MinDist = FMath::Min(MinDist, Dist);
		}

		if (MinDist >= MinDistance)
		{
			return NewColor;
		}

		if (MinDist > BestMinDist)
		{
			BestMinDist = MinDist;
			BestColor = NewColor;
		}
	}

	return BestColor;
}



ALevelSetup::ALevelSetup()
{
}

void ALevelSetup::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALevelSetup::InitializeLevel, 0.1f, false);
}

void ALevelSetup::InitializeLevel()
{
	TArray<ABaseCharacter*> allPlayers { 
		StaticCast<ABaseCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) 
	};

	UGI_LevelData* levelData = Cast<UGI_LevelData>(GetGameInstance());
	this->NumberOfAI = levelData->NumberOfAI;

	TArray<FLinearColor> existingColor{ allPlayers[0]->ColorIdentity };

	float currentPosition = 1000;
	FTransform trans;
	trans.SetLocation(FVector(currentPosition));

	for (size_t i = 0; i < NumberOfAI; ++i)
	{
		auto ai = GetWorld()->SpawnActor<AAiCharacter>(AAiCharacter::StaticClass(), trans);
		ai->ColorIdentity = GetRandomDistinctColor(existingColor).ToFColor(true);
		existingColor.Add(ai->ColorIdentity);
		allPlayers.Add(ai);

		currentPosition += 1000;
		trans.SetLocation(FVector(currentPosition));
	}

	auto aiPlayer = GetWorld()->SpawnActor<AAiCharacter>(AAiCharacter::StaticClass(), trans);
	aiPlayer->ColorIdentity = allPlayers[0]->ColorIdentity;
	StaticCast<APlayerCharacter*>(allPlayers[0])->AiPlayer = aiPlayer;

	TArray<AActor*> allRegions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegion::StaticClass(), allRegions);

	if (RandomSpawn)
	{
		Algo::RandomShuffle(allRegions);

		int playerIndex = 0;
		ABaseCharacter* currentPlayer = allPlayers[playerIndex];
		int unitLeft = levelData->StartingAmount;
		int maxRegions = allRegions.Num() / allPlayers.Num();
		int currentRegionsCount = 1;

		for (size_t i = 0; i < allRegions.Num(); ++i)
		{
			ARegion* region = StaticCast<ARegion*>(allRegions[i]);
			int unitsToPlace = 1;

			if (currentRegionsCount == maxRegions) {

				unitsToPlace += unitLeft;
				unitLeft = 0;
			}
			else if (unitLeft > 0)
			{
				int extraUnits = FMath::RandRange(0, FMath::Max(unitLeft / (maxRegions - currentRegionsCount), 5));
				unitsToPlace += extraUnits;
				unitLeft -= extraUnits;		
			}

			currentRegionsCount++;
			region->ChangeOwnerShip(currentPlayer, unitsToPlace);
			
			//At the end of the players list, but still have some region to distribute
			if (playerIndex >= allPlayers.Num())
			{
				currentPlayer = allPlayers[FMath::RandRange(0, allPlayers.Num() - 1)];
			}
			else if (currentRegionsCount > maxRegions)
			{
				playerIndex++;
				if (playerIndex < allPlayers.Num())
				{
					currentPlayer = allPlayers[playerIndex];
					unitLeft = levelData->StartingAmount;
					currentRegionsCount = 1;
				}
			}
		}

		if (unitLeft != 0)
		{
			ARegion* region = StaticCast<ARegion*>(allRegions.Last());
			region->DeployUnits(unitLeft);
		}
	}
	else 
	{
		for (AActor* actor : allRegions)
		{
			ARegion* region = StaticCast<ARegion*>(actor);
			region->ChangeOwnerShip(allPlayers[region->OwnerIdStart], 1);
		}
	}

	auto turnManager = StaticCast<ATurnManager*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
	turnManager->Initialize(&allPlayers);
}