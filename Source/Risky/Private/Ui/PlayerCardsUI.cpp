// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerCardsUI.h"
#include "Manager/CardManager.h"
#include "Ui/CardUI.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include <Ui/DragUI.h>
#include "Ui/BaseButton.h"
#include "Ui/MainUI.h"
#include "Components/Button.h"
#include "Character/CharacterCard.h"
#include "Character/PlayerCharacter.h"


void UPlayerCardsUI::NativeConstruct()
{
	Super::NativeConstruct();

	UseButton->SetButtonText("Use");
	UseButton->Button->OnClicked.AddDynamic(this, &UPlayerCardsUI::ConsumeSelectedCards);

	CloseButton->SetButtonText("X");
	CloseButton->Button->OnClicked.AddDynamic(this, &UPlayerCardsUI::HideCardsList);

	LeftCard->PlayerCards = this;
	RightCard->PlayerCards = this;
	CenterCard->PlayerCards = this;
}


void UPlayerCardsUI::UpdateCardsUi()
{

}

void UPlayerCardsUI::ConsumeSelectedCards()
{
	int32 amount = CharacterCard->ConsumeCards(CenterCard->GetCardData(), LeftCard->GetCardData(), RightCard->GetCardData());

	Player->IncreaseDeploymentUnits(amount);

	LeftCard->ClearCurrentCard();
	RightCard->ClearCurrentCard();
	CenterCard->ClearCurrentCard();
}

bool UPlayerCardsUI::NativeOnDrop(const FGeometry& geometry, const FDragDropEvent& dragDropEvent, UDragDropOperation* operation)
{
	Super::NativeOnDrop(geometry, dragDropEvent, operation);

	UDragUI* dragWidget = Cast<UDragUI>(operation);

	if (!IsValid(dragWidget)) {
		return false;
	}
	else {
		AddCard(dragWidget->WidgetReference);
		return true;
	}
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

	FCardDataUI* carddata = new FCardDataUI(icon, card, this);

	auto cardUi = CreateWidget<UCardUI>(GetWorld(), CardClass);

	cardUi->Init(carddata);

	AddCard(cardUi);
}

void UPlayerCardsUI::AddCard(UUserWidget* widget)
{
	UHorizontalBoxSlot* slot = CardsList->AddChildToHorizontalBox(widget);
	if (slot)
	{
		// (Left, Top, Right, Bottom)
		slot->SetPadding(FMargin(0, 0, 16, 0)); 
	}
	widget->SetVisibility(ESlateVisibility::Visible);

	Check3CardsSelected();
}

void UPlayerCardsUI::ShowCardsList()
{
	SetVisibility(ESlateVisibility::Visible);
	
	for (UWidget* widget : CardsList->GetAllChildren())
	{
		if (UCardUI* cardWidget = Cast<UCardUI>(widget))
		{
			cardWidget->UpdateColor();
		}
	}

	Check3CardsSelected();
}

void UPlayerCardsUI::HideCardsList()
{
	MainUIReference->UiHasClosed();
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerCardsUI::Check3CardsSelected()
{
	if (Player->GetCurrentPhase() == EGamePhase::DeploymentPhase && LeftCard->HasACard() && RightCard->HasACard() && CenterCard->HasACard())
	{
		if (CharacterCard->CanConsumeCards(LeftCard->GetCardData(), RightCard->GetCardData(), CenterCard->GetCardData()))
		{
			UseButton->SetIsEnabled(true);
		}
	}
	else
	{
		UseButton->SetIsEnabled(false);
	}
}
