// Fill out your copyright notice in the Description page of Project Settings.


#include "Province.h"
#include "Region.h"

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

bool AProvince::IsRegionInProvince(ARegion* region)
{
	return Regions.Contains(region);
}

