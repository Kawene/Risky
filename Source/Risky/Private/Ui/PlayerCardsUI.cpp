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


void UPlayerCardsUI::NativeConstruct()
{
	Super::NativeConstruct();

	UseButton->SetButtonText("Use");
	UseButton->Button->OnClicked.AddDynamic(this, &UPlayerCardsUI::ConsumeSelectedCards);

	CloseButton->SetButtonText("X");
	CloseButton->Button->OnClicked.AddDynamic(this, &UPlayerCardsUI::HideCardsList);
}


void UPlayerCardsUI::UpdateCardsUi()
{

}

void UPlayerCardsUI::ConsumeSelectedCards()
{

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

	FCardDataUI* carddata = new FCardDataUI(icon, card->Region, card->CardType, this);

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
}

void UPlayerCardsUI::HideCardsList()
{
	MainUIReference->UiHasClosed();
	SetVisibility(ESlateVisibility::Hidden);
}
