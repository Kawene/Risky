// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCard.generated.h"

UCLASS()
class RISKY_API UCharacterCard : public UObject
{
	GENERATED_BODY()

	int32 infantryValue = 6;
	int32 cavalryValue = 8;
	int32 artilleryValue = 10;
	int32 differentValue = 12;

	TArray<struct FCard*> Cards;

	int32 CurrentCardConsumed = 0;

	bool AreCommonType(FCard* card1, FCard* card2, ECardType type);

public:
	class ACardManager* CardManager;

	class ABaseCharacter* Character;

	int32 ConsumeCards(FCard* centerCard, FCard* leftCard, FCard* rightCard);

	bool CanConsumeCards(FCard* card1, FCard* card2, FCard* card3);

	FCard* AddCard();

	void ResetCounter();

	bool AlreadyHasCardWithRegion(class ARegion* region);

	void CheckRegionBonusCard(FCard* centerCard, FCard* leftCard, FCard* rightCard);

};
