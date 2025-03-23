// Fill out your copyright notice in the Description page of Project Settings.


#include "Region.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TextRenderComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter.h"

ARegion::ARegion()
{
	RegionSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RegionSceneComponent"));
	RegionSceneComponent->SetupAttachment(RootComponent);

	RegionText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RegionText"));
	RegionText->SetupAttachment(RegionSceneComponent);

	RegionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RegionMesh"));
	RegionMesh->SetupAttachment(RegionSceneComponent);
	RegionMesh->OnClicked.AddDynamic(this, &ARegion::OnSelectedRegion);
}


void ARegion::OnSelectedRegion(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->OnClickRegion(this);
}

bool ARegion::IsConnected(ARegion* otherRegion)
{
	TArray<ARegion*> alreadyVisited;
	return Looping(otherRegion, &alreadyVisited);
}

bool ARegion::Looping(ARegion* regionToLookFor, TArray<ARegion*>* alreadyVisited)
{
	if (alreadyVisited->Contains(this) || regionToLookFor->GetRegionOwner() != RegionOwner)
	{
		return false;
	}

	if (regionToLookFor == this)
	{
		return true;
	}

	alreadyVisited->Add(this);

	for (auto region : BorderingRegions)
	{
		if (region->Looping(regionToLookFor, alreadyVisited))
		{
			return true;
		}
	}
	return false;
}


int32 ARegion::GetUnits()
{
	return UnitsInRegion;
}

AProvince* ARegion::GetProvince()
{
	return Province;
}

ABaseCharacter* ARegion::GetRegionOwner()
{
	return RegionOwner;
}

const TArray<ARegion*>& ARegion::GetBorderingRegions()
{
	return BorderingRegions;
}

void ARegion::DeployUnits(int32 unitsAmount)
{
	UnitsInRegion += unitsAmount;
	RegionText->SetText(FText::AsNumber(UnitsInRegion));
}

void ARegion::DecreaseUnitCount(int32 unitsRemoved)
{
	int value = UnitsInRegion - unitsRemoved;
	UnitsInRegion = FMath::Max(value, 0);
	RegionText->SetText(FText::AsNumber(UnitsInRegion));
}

bool ARegion::HasEnoughUnits()
{
	return UnitsInRegion > 1;
}

bool ARegion::CanAttackThisRegion(ARegion* defendingRegion)
{
	return HasEnoughUnits()
		&& defendingRegion != nullptr
		&& defendingRegion->GetRegionOwner() != GetRegionOwner()
		&& BorderingRegions.Contains(defendingRegion);
}

bool ARegion::CanFortifyThisRegion(ARegion* otherRegion)
{
	return HasEnoughUnits()
		&& otherRegion != nullptr
		&& otherRegion->GetRegionOwner() == GetRegionOwner()
		&& IsConnected(otherRegion);
}

void ARegion::ToggleSelection(bool turnOff)
{
	FVector currentScale = GetActorScale3D();
	FVector newScale;
	if (IsSelected || turnOff)
	{
		newScale = currentScale / 1.3;
		IsSelected = false;
	}
	else
	{
		newScale = currentScale * 1.3;
		IsSelected = true;
	}

	SetActorScale3D(newScale);
	
	/*RegionMesh->MarkRenderStateDirty();
	if (RegionMesh->CustomDepthStencilValue == 2 || turnOff)
	{
		RegionMesh->CustomDepthStencilValue = 0;
	}
	else
	{
		RegionMesh->CustomDepthStencilValue = 2;
	}*/
}



void ARegion::ChangeOwnerShip(ABaseCharacter* newOwner, int32 unitsAmount)
{
	if (RegionOwner)
	{
		RegionOwner->RegionsOwned.Remove(this);
		RegionOwner->IsCharacterDead();
	}

	newOwner->RegionsOwned.Add(this);
	RegionOwner = newOwner;

	UnitsInRegion = unitsAmount;
	RegionText->SetText(FText::AsNumber(UnitsInRegion));

	auto newMaterial = RegionMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, RegionMesh->GetMaterial(0));
	FVector newColor = FVector(newOwner->ColorIdentity.R / 255.0f, newOwner->ColorIdentity.G / 255.0f, newOwner->ColorIdentity.B / 255.0f);
	newMaterial->SetVectorParameterValue(FName("color"), newColor);
}


