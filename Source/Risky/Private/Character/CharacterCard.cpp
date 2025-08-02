// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCard.h"
#include "Manager/CardManager.h"
#include "Region.h"


bool UCharacterCard::AreCommonType(FCard* card1, FCard* card2, ECardType type)
{
	return card1->CardType == card2->CardType ||
		card1->CardType == type && card2->CardType == ECardType::Joker ||
		card2->CardType == type && card1->CardType == ECardType::Joker;
}

int32 UCharacterCard::ConsumeCards(FCard* centerCard, FCard* leftCard, FCard* rightCard)
{
	Cards.Remove(centerCard);
	Cards.Remove(leftCard);
	Cards.Remove(rightCard);

	CheckRegionBonusCard(centerCard, leftCard, rightCard);

	switch (centerCard->CardType)
	{
	case ECardType::Infantry:
		if (AreCommonType(leftCard, rightCard, ECardType::Infantry))
		{
			return infantryValue;
		}
		break;
	case ECardType::Cavalry:
		if (AreCommonType(leftCard, rightCard, ECardType::Cavalry))
		{
			return cavalryValue;
		}
		break;
	case ECardType::Artillery:
		if (AreCommonType(leftCard, rightCard, ECardType::Artillery))
		{
			return artilleryValue;
		}
		break;

	case ECardType::Joker:
		if (leftCard->CardType == ECardType::Infantry && rightCard->CardType == ECardType::Infantry)
		{
			return infantryValue;
		}
		else if (leftCard->CardType == ECardType::Cavalry && rightCard->CardType == ECardType::Cavalry) {
			return cavalryValue;
		}
		else if (leftCard->CardType == ECardType::Artillery && rightCard->CardType == ECardType::Artillery) {
			return artilleryValue;
		}
	}

	return differentValue;

	//Other ruling : 2, 4, 6, 8, 10, 15, 20, 25...
}

bool UCharacterCard::CanConsumeCards(FCard* card1, FCard* card2, FCard* card3)
{
	if (card1->CardType == ECardType::Joker || card2->CardType == ECardType::Joker || card3->CardType == ECardType::Joker)
		return true;
	else if (card1->CardType == card2->CardType && card1->CardType == card2->CardType)
		return true;
	else if (
		card1->CardType != card2->CardType && 
		card1->CardType != card3->CardType && 
		card2->CardType != card3->CardType) 
		return true;

	return false;
}

FCard* UCharacterCard::AddCard()
{
	if (CurrentCardConsumed <= 10)
	{
		FCard* newCard = CardManager->GetCard(this);

		Cards.Add(newCard);

		++CurrentCardConsumed;

		return newCard;
	}

	return nullptr;
}

void UCharacterCard::ResetCounter()
{
	CurrentCardConsumed = 0;
}

bool UCharacterCard::AlreadyHasCardWithRegion(ARegion* region)
{
	for (FCard* card : Cards)
	{
		if (card->Region == region)
		{
			return true;
		}
	}

	return false;
}

void UCharacterCard::CheckRegionBonusCard(FCard* centerCard, FCard* leftCard, FCard* rightCard)
{
	if (Character == centerCard->Region->GetRegionOwner())
	{
		centerCard->Region->DeployUnits(2);
	}
	else if (Character == leftCard->Region->GetRegionOwner())
	{
		leftCard->Region->DeployUnits(2);
	}
	else if (Character == rightCard->Region->GetRegionOwner())
	{
		rightCard->Region->DeployUnits(2);
	}
}
