// Fill out your copyright notice in the Description page of Project Settings.


#include "Region.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
ARegion::ARegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RegionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RegionMesh"));
	RegionMesh->SetupAttachment(RootComponent);
	RegionMesh->OnClicked.AddDynamic(this, &ARegion::OnSelectedRegion);
	RegionText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RegionText"));
	RegionText->SetupAttachment(RegionMesh);
}

// Called when the game starts or when spawned
void ARegion::BeginPlay()
{
	Super::BeginPlay();
}

void ARegion::OnSelectedRegion(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->SelectRegion(this);
}

// Called every frame
void ARegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ARegion::GetUnits()
{
	return UnitsInRegion;
}

const ABaseCharacter* ARegion::GetRegionOwner()
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

void ARegion::ChangeOwnerShip(ABaseCharacter* newOwner, int32 unitsAmount)
{
	RegionOwner = newOwner;
	UnitsInRegion = unitsAmount;
	RegionText->SetText(FText::AsNumber(UnitsInRegion));
}


