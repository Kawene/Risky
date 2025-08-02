// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/CardUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Manager/CardManager.h"
#include "Region.h"
#include "Character/BaseCharacter.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "Ui/DragUI.h"
#include "Ui/PlayerCardsUI.h"

FReply UCardUI::NativeOnMouseButtonDown(const FGeometry& geometry, const FPointerEvent& mouseEvent)
{
	if (IsInList)
	{
		Super::NativeOnMouseButtonDown(geometry, mouseEvent);
		return UWidgetBlueprintLibrary::DetectDragIfPressed(mouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	else 
	{
		ReplaceIntoList();
		return Super::NativeOnMouseButtonDown(geometry, mouseEvent);
	}
}

void UCardUI::NativeOnDragDetected(const FGeometry& geometry, const FPointerEvent& pointerEvent, UDragDropOperation*& operation)
{
	Super::NativeOnDragDetected(geometry, pointerEvent, operation);

	UDragUI* dragWidget = Cast<UDragUI>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragUI::StaticClass()));
	SetVisibility(ESlateVisibility::HitTestInvisible);

	dragWidget->WidgetReference = this;

	dragWidget->DefaultDragVisual = this;
	dragWidget->Pivot = EDragPivot::MouseDown;

	operation = dragWidget;

	IsInList = false;
	RemoveFromParent();
}


void UCardUI::Init(FCardDataUI* cardData)
{
	Parent = cardData->Parent;
	CardData = cardData->Card;
	IsInList = true;

	RegionName->SetText(CardData->Region->GetRegionName());

	CardTypeIcon->SetBrushFromTexture(cardData->Icon);
	UpdateColor();
}

void UCardUI::ReplaceIntoList()
{
	IsInList = true;
	Parent->AddCard(this);
}

void UCardUI::UpdateColor()
{
	RegionVisual->SetColorAndOpacity(CardData->Region->GetRegionOwner()->ColorIdentity.ReinterpretAsLinear());
}
