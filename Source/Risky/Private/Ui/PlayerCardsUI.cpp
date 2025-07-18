// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerCardsUI.h"
#include "Manager/CardManager.h"
#include "Ui/CardUI.h"
#include "Components/ListView.h"
#include <CardData.h>

void UPlayerCardsUI::UpdateCardsUi()
{

}

void UPlayerCardsUI::AddCard(FCard* card)
{
	UTexture2D* icon = nullptr;

	switch (card->CardType)
	{
	case ECardType::Infantry:
		icon = InfantryIcon;
		break;
	case ECardType::Cavalry:
		icon = CalvalryIcon;
		break;
	case ECardType::Artillery:
		icon = ArtilleryIcon;
		break;
	case ECardType::Joker:
		icon = JokerIcon;
		break;
	}

	UCardData* carddata = NewObject<UCardData>();
	carddata->Icon = icon;
	carddata->Region = card->Region;
	carddata->CardType = card->CardType;

	CardsList->AddItem(carddata);
}

void UPlayerCardsUI::ShowCardsList()
{
	SetVisibility(ESlateVisibility::Visible);
	
	for (UUserWidget* widget : CardsList->GetDisplayedEntryWidgets())
	{
		if (UCardUI* cardWidget = Cast<UCardUI>(widget))
		{
			cardWidget->UpdateColor();
		}
	}
}

void UPlayerCardsUI::HideCardsList()
{
	SetVisibility(ESlateVisibility::Hidden);
}
