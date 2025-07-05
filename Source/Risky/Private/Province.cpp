// Fill out your copyright notice in the Description page of Project Settings.


#include "Province.h"
#include "Region.h"
#include "Character/BaseCharacter.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h"
#include <Kismet/GameplayStatics.h>

void AProvince::BeginPlay()
{
	Super::BeginPlay();
	BonusText->SetText(FText::FromString(FString::Printf(TEXT("+ %d"), Bonus)));

	HideDetails();
}

AProvince::AProvince()
{
	ProvinceSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProvinceSceneComponent"));
	ProvinceSceneComponent->SetupAttachment(RootComponent);

	BonusText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BonusText"));
	BonusText->SetupAttachment(ProvinceSceneComponent);

	RegionOwnedRatioText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RegionsText"));
	RegionOwnedRatioText->SetupAttachment(BonusText);
}

int32 AProvince::GetBonusIfOwner(ABaseCharacter* character)
{
	if (HasControlOverProvince(character))
		return Bonus;
	else
		return 0;
}

bool AProvince::HasControlOverProvince(ABaseCharacter* character)
{
	for (ARegion* region : Regions)
	{
		if (region->GetRegionOwner() != character)
		{
			return false;
		}
	}
	return true;
}

bool AProvince::SomeoneHasControl()
{
	for (size_t i = 1; i < Regions.Num(); ++i)
	{
		if (Regions[0]->GetRegionOwner() != Regions[i]->GetRegionOwner())
		{
			return false;
		}
	}
	return true;
}

bool AProvince::IsRegionInProvince(ARegion* region)
{
	return Regions.Contains(region);
}

void AProvince::ViewDetails()
{
    ABaseCharacter* owner = nullptr;
    if (SomeoneHasControl())
    {
        owner = Regions[0]->GetRegionOwner();
    }

    FLinearColor meshColor;
    if (owner)
    {
        meshColor = owner->ColorIdentity.ReinterpretAsLinear();
    }
    else
    {
        meshColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);
    }

    for (auto mesh : ProvinceMesh)
    {
		UStaticMeshComponent* meshComponent = mesh->GetStaticMeshComponent();

		auto newMaterial = meshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, meshComponent->GetMaterial(0));
		newMaterial->SetVectorParameterValue(FName("color"), meshColor);
		mesh->SetActorHiddenInGame(false);
    }


	auto player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int totalOwned = 0;

	for (ARegion* region : Regions)
	{
		if (region->GetRegionOwner() == player)
		{
			++totalOwned;
		}
	}

	auto regionOwnedRatio = FString::Printf(TEXT("%d/%d"), totalOwned, Regions.Num());
	RegionOwnedRatioText->SetText(FText::FromString(regionOwnedRatio));

	BonusText->SetVisibility(true);
	RegionOwnedRatioText->SetVisibility(true);
}

void AProvince::HideDetails()
{
	for (auto mesh : ProvinceMesh)
	{
		mesh->SetActorHiddenInGame(true);
	}

	BonusText->SetVisibility(false);
	RegionOwnedRatioText->SetVisibility(false);
}

