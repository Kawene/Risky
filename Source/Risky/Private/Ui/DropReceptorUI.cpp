// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DropReceptorUI.h"
#include "UI/DragUI.h"
#include "Components/Border.h"
#include <UI/CardUI.h>
#include "UI/PlayerCardsUI.h"

bool UDropReceptorUI::NativeOnDrop(const FGeometry& geometry, const FDragDropEvent& dragDropEvent, UDragDropOperation* operation)
{
	Super::NativeOnDrop(geometry, dragDropEvent, operation);

	UDragUI* dragWidget = Cast<UDragUI>(operation);

	if (!IsValid(dragWidget)) {
		return false;
	}

	if (HasACard())
	{
		Cast<UCardUI>(ReceptorBorder->GetAllChildren()[0])->ReplaceIntoList();
	}

	ReceptorBorder->AddChild(dragWidget->WidgetReference);
	dragWidget->WidgetReference->SetVisibility(ESlateVisibility::Visible);

	PlayerCards->Check3CardsSelected();

	return true;
}

bool UDropReceptorUI::HasACard()
{
	return ReceptorBorder->HasAnyChildren();
}

FCard* UDropReceptorUI::GetCardData()
{
	if (ReceptorBorder->HasAnyChildren())
	{
		return Cast<UCardUI>(ReceptorBorder->GetAllChildren()[0])->GetCardData();
	}
	return nullptr;
}

void UDropReceptorUI::ClearCurrentCard()
{
	if (ReceptorBorder->HasAnyChildren())
	{
		ReceptorBorder->ClearChildren();
	}
}
