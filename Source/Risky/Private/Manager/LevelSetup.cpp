// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/LevelSetup.h"
#include "Character/BaseCharacter.h"
#include "Character/AiCharacter.h"
#include "Region.h"
#include "Manager/TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

FColor GetRandomColor()
{
	int32 red = FMath::RandRange(0, 255);
	int32 green = FMath::RandRange(0, 255);
	int32 blue = FMath::RandRange(0, 255);
	FColor newColor = FColor(red, green, blue);

	return newColor;
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


	for (size_t i = 0; i < NumberOfAI; ++i)
	{
		auto ai = GetWorld()->SpawnActor<AAiCharacter>(AAiCharacter::StaticClass());
		ai->ColorIdentity = GetRandomColor();
		allPlayers.Add(ai);
	}

	TArray<AActor*> allRegions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegion::StaticClass(), allRegions);

	for (AActor* actor : allRegions)
	{
		ARegion* region = StaticCast<ARegion*>(actor);
		region->ChangeOwnerShip(allPlayers[region->OwnerIdStart], 1);
	}

	auto turnManager = GetWorld()->SpawnActor<ATurnManager>(ATurnManager::StaticClass());
	turnManager->Initialize(&allPlayers);
}