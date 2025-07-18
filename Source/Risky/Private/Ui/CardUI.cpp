// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/CardUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Manager/CardManager.h"
#include "CardData.h"
#include "Region.h"
#include "Character/BaseCharacter.h"


void UCardUI::NativeOnListItemObjectSet(UObject* listItemObject)
{
	UCardData* cardData = StaticCast<UCardData*>(listItemObject);

	Region = cardData->Region;
	CardType = cardData->CardType;

	RegionName->SetText(Region->GetRegionName());

	CardTypeIcon->SetBrushFromTexture(cardData->Icon);
	UpdateColor();
}

void UCardUI::UpdateColor()
{
	RegionVisual->SetColorAndOpacity(Region->GetRegionOwner()->ColorIdentity.ReinterpretAsLinear());
}
