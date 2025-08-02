// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardManager.generated.h"


UENUM(BlueprintType)
enum class ECardType: uint8 {
	Infantry = 0,
	Cavalry = 1,
	Artillery = 2,
	Joker = 3
};


USTRUCT(BlueprintType)
struct FCard
{
	GENERATED_BODY()

	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	class ARegion* Region;

	FCard(){}

	FCard(ECardType cardType, ARegion* region)
		: CardType(cardType), Region(region) {
	} 

	bool operator==(const FCard& other) const {
		return CardType == other.CardType && Region == other.Region;
	}
};

UCLASS()
class RISKY_API ACardManager : public AActor
{
	GENERATED_BODY()

	TArray<ECardType> CardPool;

	TArray<AActor*> Regions;

	void GeneratePool();
	
public:	

	FCard* GetCard(class UCharacterCard* characterCard);

protected:
	virtual void BeginPlay() override;
};
