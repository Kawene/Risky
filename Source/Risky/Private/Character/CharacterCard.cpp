// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCard.h"
#include "Manager/CardManager.h"


bool UCharacterCard::AreCommonType(FCard* card1, FCard* card2, ECardType type)
{
	return card1->CardType == card2->CardType ||
		card1->CardType == type && card2->CardType == ECardType::Joker ||
		card2->CardType == type && card1->CardType == ECardType::Joker;
}

int32 UCharacterCard::ConsumeCards(FCard* card1, FCard* card2, FCard* card3)
{
	Cards.Remove(card1);
	Cards.Remove(card2);
	Cards.Remove(card3);

	switch (card1->CardType)
	{
	case ECardType::Infantry:
		if (AreCommonType(card2, card3, ECardType::Infantry))
		{
			return infantryValue;
		}
		break;
	case ECardType::Cavalry:
		if (AreCommonType(card2, card3, ECardType::Cavalry))
		{
			return cavalryValue;
		}
		break;
	case ECardType::Artillery:
		if (AreCommonType(card2, card3, ECardType::Artillery))
		{
			return artilleryValue;
		}
		break;

	case ECardType::Joker:
		if (card2->CardType == ECardType::Infantry && card3->CardType == ECardType::Infantry)
		{
			return infantryValue;
		}
		else if (card2->CardType == ECardType::Cavalry && card3->CardType == ECardType::Cavalry) {
			return cavalryValue;
		}
		else if (card2->CardType == ECardType::Artillery && card3->CardType == ECardType::Artillery) {
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
