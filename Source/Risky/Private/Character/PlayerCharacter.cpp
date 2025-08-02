// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Character/AiCharacter.h"
#include "Character/CharacterCard.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Risky/RiskyPlayerController.h"
#include "Manager/TurnManager.h"
#include "Ui/MainUI.h"
#include "Region.h"
#include "AttackResults.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


void APlayerCharacter::SelectRegion(ARegion** regionToModify, ARegion* regionSelected) {
	*regionToModify = regionSelected;
	(*regionToModify)->ToggleSelection();

	ZoomCameraToRegion(*regionToModify);
}


void APlayerCharacter::DeselectRegion(ARegion** region, bool deZoom) {
	if (*region)
	{
		if ((*region)->GetRegionOwner() == this && deZoom)
		{
			DeZoomCamera();
		}

		(*region)->ToggleSelection();
		(*region) = nullptr;
	}
}

void APlayerCharacter::ZoomCameraToRegion(ARegion* regionSelected)
{
	if (regionSelected->GetRegionOwner() == this && CurrentPhase != EGamePhase::FortificationPhase)
	{
		if (CameraZoomedIn)
		{
			MoveCameraToRegion(regionSelected);
			return;
		}
		
		CameraZoomedIn = true;
		PreviousCameraTargetArmLength = CameraBoom->TargetArmLength;
		CameraTargetArmLength = CameraBoom->TargetArmLength * 0.5f;
		MoveCameraToPosition(regionSelected->GetActorLocation());
	}
}

void APlayerCharacter::MoveCameraToRegion(ARegion* regionSelected)
{
	if (regionSelected->GetRegionOwner() == this)
	{
		MoveCameraToPosition(regionSelected->GetActorLocation());
	}
}

void APlayerCharacter::MoveCameraToPosition(FVector position)
{
	CameraMoving = true;
	CameraTargetLocation = position;
}

void APlayerCharacter::DeZoomCamera()
{
	if (CameraZoomedIn)
	{
		CameraZoomedIn = false;
		CameraTargetArmLength = PreviousCameraTargetArmLength;
		MoveCameraToPosition(GetActorLocation() + FVector(0, 0, 1000));
	}
}

void APlayerCharacter::IncreaseDeploymentUnits(int32 amount)
{
	CurrentUnitsToDeploy += amount;

	TurnManager->UpdateTurnTrackerUI(this, CurrentUnitsToDeploy);
}

void APlayerCharacter::AddCard()
{
	if (auto card = CharacterCard->AddCard())
	{
		PlayerHUD->AddCardToUi(card);
	}	
}

APlayerCharacter::APlayerCharacter() : ABaseCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 10000.f;
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentPhase = EGamePhase::NotCurrentTurn;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CameraMoving)
	{
		FVector currentLocation = CameraBoom->GetComponentLocation();
		float currentArmLength = CameraBoom->TargetArmLength;

		float dist = FVector::Dist(currentLocation, CameraTargetLocation);

		float alpha = FMath::Clamp(DeltaTime * 4.5f, 0.0f, 1.0f); 

		if (dist < 200)
			alpha = FMath::Clamp(DeltaTime * 9.0f, 0.0f, 1.0f);
		else if (dist < 400.f) 
			alpha = FMath::Clamp(DeltaTime * 7.5f, 0.0f, 1.0f);
		else if (dist < 650.f)
			alpha = FMath::Clamp(DeltaTime * 6.0f, 0.0f, 1.0f);

		FVector newLocation = FMath::Lerp(currentLocation, CameraTargetLocation, alpha);
		float newArmLength = FMath::Lerp(currentArmLength, CameraTargetArmLength, alpha);

		CameraBoom->SetWorldLocation(newLocation);
		CameraBoom->TargetArmLength = newArmLength;

		if (FVector::Dist(newLocation, CameraTargetLocation) < 20.f && FMath::Abs(newArmLength - CameraTargetArmLength) < 10.f)
		{
			CameraMoving = false;
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && PlayerHUDClass)
	{
		ARiskyPlayerController* controller = GetController<ARiskyPlayerController>();
		check(controller);
		PlayerHUD = CreateWidget<UMainUI>(controller, PlayerHUDClass);
		PlayerHUD->InitializeUI(this, controller);
		check(PlayerHUD);
	}

}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void APlayerCharacter::DeployUnitsToSelectedRegion(int32 unitsToDeploy)
{
	if (CurrentUnitsToDeploy >= unitsToDeploy)
	{
		CurrentUnitsToDeploy -= unitsToDeploy;
		FirstSelectedRegion->DeployUnits(unitsToDeploy);
		DeselectRegion(&FirstSelectedRegion);
		if (CurrentUnitsToDeploy == 0)
		{
			FinishedCurrentPhase();
		}
		else 
		{
			TurnManager->UpdateTurnTrackerUI(this, CurrentUnitsToDeploy);
		}
	}
}

FAttackResults* APlayerCharacter::DeclareAttack(int32 attackerAmount)
{
	FAttackResults* attackResults = Super::GetDiceResults(SecondSelectedRegion, attackerAmount);

	return attackResults;
}

int32 APlayerCharacter::ApplyAttackResults(FAttackResults* results)
{
	if (FirstSelectedRegion && SecondSelectedRegion)
	{
		Super::ExecuteAttack(FirstSelectedRegion, SecondSelectedRegion, results);
		TurnManager->UpdateTurnTrackerUI(this);
		if (SecondSelectedRegion->GetUnits() == 0)
		{
			auto niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CaptureEffectNiagara, 
				SecondSelectedRegion->GetActorLocation(),
				FRotator::ZeroRotator,
				SecondSelectedRegion->GetRegionScale() + FVector(1,1,3));

			niagara->SetVariableLinearColor(FName("User.Color"), ColorIdentity);

			SecondSelectedRegion->ChangeOwnerShip(this, 0);

			AddCard();

			return 0;
		}

		if (!FirstSelectedRegion->HasEnoughUnits())
		{
			DeselectRegion(&FirstSelectedRegion);
			DeselectRegion(&SecondSelectedRegion);
			return -1;
		}

		return SecondSelectedRegion->GetUnits();
	}
	return 0;
}

void APlayerCharacter::FinishedCurrentPhase()
{
	if (CurrentPhase == EGamePhase::FortificationPhase)
	{
		CurrentPhase = EGamePhase::NotCurrentTurn;
		ChangeGamePhase.Execute(CurrentPhase);
	}
	 
	DeselectRegion(&FirstSelectedRegion);

	DeselectRegion(&SecondSelectedRegion);

	Super::FinishedCurrentPhase();
}

void APlayerCharacter::TransferAmount(int32 amount)
{
	TransferUnits(FirstSelectedRegion, SecondSelectedRegion, amount);

	bool canStillAttack = false;
	for (ARegion* region : SecondSelectedRegion->GetBorderingRegions())
	{
		if (region->GetRegionOwner() != this)
		{
			canStillAttack = true;
			break;
		}
	}

	bool continueZoom = amount > 1 && CurrentPhase == EGamePhase::AttackPhase && canStillAttack;

	if (continueZoom)
	{
		ARegion* temp = SecondSelectedRegion;

		DeselectRegion(&FirstSelectedRegion, false);
		DeselectRegion(&SecondSelectedRegion, false);

		SelectRegion(&FirstSelectedRegion, temp);
	}
	else 
	{
		DeselectRegion(&FirstSelectedRegion);
		DeselectRegion(&SecondSelectedRegion);
	}
}

void APlayerCharacter::DialogAction(int32 units)
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		DeployUnitsToSelectedRegion(units);
		break;
	case EGamePhase::AttackPhase:
		TransferAmount(units);
		break;
	case EGamePhase::FortificationPhase:
		TransferAmount(units);
		FinishedCurrentPhase();
		break;
	}
}

void APlayerCharacter::IsCharacterDead()
{
	if (RegionsOwned.IsEmpty() && !TurnManager->InSimulation)
	{
		TurnManager->CharacterDied(this);
		PlayerHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerCharacter::SetUiOpen(bool isOpen)
{
	if (!isOpen)
	{
		PlayerHUD->UiHasClosed();
		switch (CurrentPhase)
		{
		case EGamePhase::DeploymentPhase:
			DeselectRegion(&FirstSelectedRegion);	
			break;
		case EGamePhase::AttackPhase:
			DeselectRegion(&SecondSelectedRegion);	
			PlayerHUD->ButtonVisibility(true);
			if (FirstSelectedRegion)
			{
				MoveCameraToRegion(FirstSelectedRegion);
			}
			break;
		case EGamePhase::FortificationPhase:
			DeselectRegion(&SecondSelectedRegion);
			break;
		}
	}
}

void APlayerCharacter::TransferTo(bool toPlayer)
{
	if (toPlayer)
	{
		TArray<ARegion*> RegionsToProcess = AiPlayer->RegionsOwned;

		if (RegionsToProcess.IsEmpty())
		{
			IsCharacterDead();
			return;
		}

		TurnManager->InSimulation = true;
		for (ARegion* region : RegionsToProcess)
		{
			region->ChangeOwnerShip(this, region->GetUnits());
		}
	}
	else {
		TurnManager->InSimulation = true;
		TArray<ARegion*> RegionsToProcess = RegionsOwned;
		for (ARegion* region : RegionsToProcess)
		{
			region->ChangeOwnerShip(AiPlayer, region->GetUnits());
		}
	}
	TurnManager->InSimulation = false;
}

void APlayerCharacter::TurnManagerRef(ATurnManager* tManager)
{
	Super::TurnManagerRef(tManager);
	AiPlayer->TurnManagerRef(tManager);
}

void APlayerCharacter::ShowVictoryScreen()
{
	PlayerHUD->CloseAttackUi();
	PlayerHUD->ShowVictoryUi();
}

void APlayerCharacter::ShowDefeatScreen()
{
	PlayerHUD->ShowDefeatUi();
}

void APlayerCharacter::SetCameraToSeeMap()
{
	//Center of the BigMap
	MoveCameraToPosition(FVector(6000, 2000, 1000));
	CameraZoomedIn = true;
	PreviousCameraTargetArmLength = CameraBoom->TargetArmLength;
	CameraTargetArmLength = 13000;
}

void APlayerCharacter::OnClickRegion(ARegion* regionSelected)
{
	if (PlayerHUD->IsUiOpen())
	{
		return;
	}

	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		if (regionSelected->GetRegionOwner() == this)
		{
			DeselectRegion(&FirstSelectedRegion);

			SelectRegion(&FirstSelectedRegion, regionSelected);

			PlayerHUD->ShowUnitsUi(CurrentUnitsToDeploy, FText::FromString("Deploy"));
		}
		break;
	case EGamePhase::AttackPhase:
		if (regionSelected->GetRegionOwner() == this)
		{
			if (FirstSelectedRegion == regionSelected)
			{
				DeselectRegion(&FirstSelectedRegion);
				DeselectRegion(&SecondSelectedRegion);
				return;
			}

			if (regionSelected->GetUnits() > 1)
			{
				DeselectRegion(&FirstSelectedRegion, false);
				SelectRegion(&FirstSelectedRegion, regionSelected);
			}

		}
		else
		{
			if (FirstSelectedRegion && FirstSelectedRegion->CanAttackThisRegion(regionSelected))
			{
				SelectRegion(&SecondSelectedRegion, regionSelected);

				MoveCameraToPosition((FirstSelectedRegion->GetActorLocation() + SecondSelectedRegion->GetActorLocation()) * 0.5);
				PlayerHUD->ButtonVisibility(false);
				PlayerHUD->ShowAttackUi(FirstSelectedRegion, SecondSelectedRegion->GetUnits(), SecondSelectedRegion->GetRegionOwner()->ColorIdentity);
			}
		}
		break;
	case EGamePhase::FortificationPhase:

		if (regionSelected->GetRegionOwner() != this)
			return;
		

	    if(FirstSelectedRegion == regionSelected)
		{
			DeselectRegion(&FirstSelectedRegion);
		}
		else if (SecondSelectedRegion == regionSelected)
		{
			DeselectRegion(&SecondSelectedRegion);
		}
		else if (!FirstSelectedRegion && regionSelected->GetUnits() > 1)
		{
			SelectRegion(&FirstSelectedRegion, regionSelected);
		}
		else if(FirstSelectedRegion)
		{
			DeselectRegion(&SecondSelectedRegion);

			SelectRegion(&SecondSelectedRegion, regionSelected);

			if (FirstSelectedRegion->CanFortifyThisRegion(SecondSelectedRegion))
			{
				PlayerHUD->ShowUnitsUi(FirstSelectedRegion->GetUnits() - 1, FText::FromString("Fortify"));
			}
		}
		break;
	case EGamePhase::NotCurrentTurn:
		break;
	}
}

void APlayerCharacter::EscapeAction()
{
	if (PlayerHUD->IsUiOpen())
	{
		PlayerHUD->CloseCurrentUi();
	}
	else 
	{
		if (FirstSelectedRegion)
		{
			DeselectRegion(&FirstSelectedRegion);
			DeselectRegion(&SecondSelectedRegion);
		}
		else {
			PlayerHUD->ToggleVisibilityPauseUi();
		}
	}
}

void APlayerCharacter::TabAction()
{
	PlayerHUD->ToggleVisibilityScoreboardUi();
}

void APlayerCharacter::StartDeploymentPhase()
{
	UGameplayStatics::PlaySound2D(this, TurnStartSound, 1.0f, 1.0f, 0.4f);
	CurrentPhase = EGamePhase::DeploymentPhase;
	CurrentUnitsToDeploy = TurnManager->GetsNumberOfUnitsToDeploy(this);
	ChangeGamePhase.Execute(CurrentPhase);
	CharacterCard->ResetCounter();
}

void APlayerCharacter::StartAttackPhase()
{
	CurrentPhase = EGamePhase::AttackPhase;
	ChangeGamePhase.Execute(CurrentPhase);
}

void APlayerCharacter::StartFortificationPhase()
{
	CurrentPhase = EGamePhase::FortificationPhase;
	ChangeGamePhase.Execute(CurrentPhase);
}
