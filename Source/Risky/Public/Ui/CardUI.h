// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Manager/CardManager.h"
#include "CardUI.generated.h"


UCLASS()
class RISKY_API UCardUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CardTypeIcon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* RegionVisual;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RegionName;

	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	class ARegion* Region;

	UPROPERTY()
	class UPlayerCardsUI* Parent;

	bool IsInList;



protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& geometry, const FPointerEvent& mouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& geometry, const FPointerEvent& pointerEvent, UDragDropOperation*& operation) override;

public:

	void Init(FCardDataUI* cardData);

	void UpdateColor();

	void ReplaceIntoList();

};

USTRUCT()
struct RISKY_API FCardDataUI
{
	GENERATED_BODY()

	FCardDataUI() {};

	FCardDataUI(class UTexture2D* icon, class ARegion* region, ECardType cardType, class UPlayerCardsUI* parent) :
	Icon(icon), Region(region), CardType(cardType), Parent(parent) {};


	UPROPERTY()
	class UTexture2D* Icon;

	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	class ARegion* Region;

	UPROPERTY()
	class UPlayerCardsUI* Parent;
};
