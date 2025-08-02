// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Manager/CardManager.h"
#include "DropReceptorUI.h"
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
	class UPlayerCardsUI* Parent;

	struct FCard* CardData;

	bool IsInList;



protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& geometry, const FPointerEvent& mouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& geometry, const FPointerEvent& pointerEvent, UDragDropOperation*& operation) override;

public:

	void Init(FCardDataUI* cardData);

	void UpdateColor();

	void ReplaceIntoList();

	FCard* GetCardData()
	{
		return CardData;
	}

};

USTRUCT()
struct RISKY_API FCardDataUI
{
	GENERATED_BODY()

	FCardDataUI() {};

	FCardDataUI(class UTexture2D* icon, struct FCard* card, class UPlayerCardsUI* parent) :
	Icon(icon), Card(card), Parent(parent) { };


	UPROPERTY()
	class UTexture2D* Icon;

	struct FCard* Card;

	UPROPERTY()
	class UPlayerCardsUI* Parent;
};
