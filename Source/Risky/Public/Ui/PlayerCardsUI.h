// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCardsUI.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API UPlayerCardsUI : public UUserWidget
{
	GENERATED_BODY()
	
	void UpdateCardsUi();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UListView* CardsList;

protected:

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* InfantryIcon;

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* CalvalryIcon;

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* ArtilleryIcon;

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* JokerIcon;

public:
	void AddCard(struct FCard* card);

	void ShowCardsList();

	void HideCardsList();
};