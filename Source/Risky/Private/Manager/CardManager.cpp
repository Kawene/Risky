// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CardManager.h"
#include "Region.h"


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

}

FCard* ACardManager::GetCard()
{
	if (CardPool.Num() > 0)
	{
		ECardType cardType = CardPool.Pop();
		ARegion* region = nullptr; // You would need to assign a valid region here
		return new FCard(cardType, region);
	}
	else {

	}
	return nullptr;
}

void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	
	GeneratePool();
}


