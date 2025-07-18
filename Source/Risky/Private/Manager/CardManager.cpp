// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CardManager.h"
#include "Region.h"
#include <Algo/RandomShuffle.h>
#include <Kismet/GameplayStatics.h>
#include "Math/UnrealMathUtility.h"
#include "Character/CharacterCard.h"

void ACardManager::GeneratePool()
{

	for (size_t i = 0; i < 35; i++)
	{
		CardPool.Add(ECardType::Infantry);
	}

	for (size_t i = 0; i < 30; i++)
	{
		CardPool.Add(ECardType::Cavalry);
	}

	for (size_t i = 0; i < 20; i++)
	{
		CardPool.Add(ECardType::Artillery);
	}

	for (size_t i = 0; i < 15; i++)
	{
		CardPool.Add(ECardType::Joker);
	}

	Algo::RandomShuffle(CardPool);
}

FCard* ACardManager::GetCard(UCharacterCard* characterCard)
{
	if (CardPool.Num() == 0)
		GeneratePool();

	ECardType cardType = CardPool.Pop();
	ARegion* region = nullptr;

	do 
	{
		region = Cast<ARegion>(Regions[FMath::RandRange(0, Regions.Num() - 1)]);
	} while (characterCard->AlreadyHasCardWithRegion(region));

	return new FCard(cardType, region);
}

void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	
	GeneratePool();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegion::StaticClass(), Regions);
}


