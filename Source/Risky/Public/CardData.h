// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Manager/CardManager.h"
#include "CardData.generated.h"



UCLASS()
class RISKY_API UCardData : public UObject
{
	GENERATED_BODY()

public:

	UCardData();

	UCardData(class UTexture2D* icon, class ARegion* region, ECardType cardType) : Icon(icon), Region(region), CardType(cardType) {}

	UPROPERTY()
	class UTexture2D* Icon;

	UPROPERTY()
	class ARegion* Region;

	UPROPERTY()
	ECardType CardType;
};
