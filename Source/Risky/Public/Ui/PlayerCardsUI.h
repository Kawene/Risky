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

	UFUNCTION()
	void ConsumeSelectedCards();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* CardsList;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* UseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* CloseButton;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCardUI> CardClass;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UDropReceptorUI* LeftCard;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UDropReceptorUI* RightCard;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UDropReceptorUI* CenterCard;

protected:

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* InfantryIcon;

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* CalvalryIcon;

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* ArtilleryIcon;

	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* JokerIcon;

	virtual bool NativeOnDrop(const FGeometry& geometry, const FDragDropEvent& dragDropEvent, UDragDropOperation* operation) override;

	virtual void  NativeConstruct();

public:
	class UMainUI* MainUIReference;

	class UCharacterCard* CharacterCard;

	class APlayerCharacter* Player;

	void AddCard(struct FCard* card);

	void AddCard(class UUserWidget* widget);

	void ShowCardsList();

	UFUNCTION()
	void HideCardsList();

	void Check3CardsSelected();
};