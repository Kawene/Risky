// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Province.generated.h"

class ARegion;

class ABaseCharacter;

UCLASS()
class RISKY_API AProvince : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<ARegion*> Regions;

	UPROPERTY(EditAnywhere)
	int32 Bonus;

	UPROPERTY(EditAnywhere)
	class USceneComponent* ProvinceSceneComponent;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* BonusText;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* RegionOwnedRatioText;

	void virtual BeginPlay() override;

public:

	AProvince();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AStaticMeshActor*> ProvinceMesh;

	int32 GetBonusIfOwner(ABaseCharacter* character);

	bool HasControlOverProvince(ABaseCharacter* character);

	bool SomeoneHasControl();

	bool IsRegionInProvince(ARegion* region);

	void ViewDetails();

	void HideDetails();
};
