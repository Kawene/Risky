// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Risky/RiskyPlayerController.h"
#include "Manager/TurnManager.h"
#include "Ui/MainUI.h"
#include "Region.h"

APlayerCharacter::APlayerCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1500.f;
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
		FirstSelectedRegion->ToggleSelection();
		FirstSelectedRegion = nullptr;
		if (CurrentUnitsToDeploy == 0)
		{
			FinishedCurrentPhase();
		}
	}
}

void APlayerCharacter::AttackSelectedRegion(int32 attackerAmount)
{
	if (FirstSelectedRegion && SecondSelectedRegion)
	{
		bool regionCaptured = Super::CombatRegion(FirstSelectedRegion, SecondSelectedRegion, attackerAmount);
		if (FirstSelectedRegion->GetUnits() == 1)
		{
			FirstSelectedRegion->ToggleSelection();
			SecondSelectedRegion->ToggleSelection();
		}
		AttackStep.Execute(regionCaptured);
	}
}

void APlayerCharacter::FinishedCurrentPhase()
{
	if (CurrentPhase == EGamePhase::FortificationPhase)
	{
		CurrentPhase = EGamePhase::NotCurrentTurn;
		ChangeGamePhase.Execute(CurrentPhase);
	}
	 
	if (FirstSelectedRegion)
	{
		FirstSelectedRegion->ToggleSelection(true);
		FirstSelectedRegion = nullptr;
	}

	if (SecondSelectedRegion)
	{
		SecondSelectedRegion->ToggleSelection(true);
		SecondSelectedRegion = nullptr;
	}

	Super::FinishedCurrentPhase();
}

void APlayerCharacter::TransferAmount(int32 amount)
{
	TransferUnits(FirstSelectedRegion, SecondSelectedRegion, amount);
	FirstSelectedRegion->ToggleSelection();
	SecondSelectedRegion->ToggleSelection();
	FirstSelectedRegion = nullptr;
	SecondSelectedRegion = nullptr;
}

void APlayerCharacter::DialogAction(int32 units)
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		DeployUnitsToSelectedRegion(units);
		break;
	case EGamePhase::AttackPhase:
		break;
	case EGamePhase::FortificationPhase:
		TransferAmount(units);
		break;
	}
}

void APlayerCharacter::SelectRegion(ARegion* regionSelected)
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		if (regionSelected->GetRegionOwner() == this)
		{
			if (FirstSelectedRegion)
			{
				FirstSelectedRegion->ToggleSelection();
			}
			FirstSelectedRegion = regionSelected;
			FirstSelectedRegion->ToggleSelection();
			PlayerHUD->ShowUnitsUi(CurrentUnitsToDeploy, FText::FromString("Deploy"));
		}
		break;
	case EGamePhase::AttackPhase:
		if (regionSelected->GetRegionOwner() == this)
		{
			if (FirstSelectedRegion == regionSelected)
			{
				FirstSelectedRegion->ToggleSelection();
				FirstSelectedRegion = nullptr;
				return;
			}

			if (FirstSelectedRegion)
			{
				FirstSelectedRegion->ToggleSelection();
			}
			FirstSelectedRegion = regionSelected;
			FirstSelectedRegion->ToggleSelection();
		}
		else
		{
			if (SecondSelectedRegion == regionSelected)
			{
				SecondSelectedRegion->ToggleSelection();
				SecondSelectedRegion = nullptr;
				return;
			}

			if (SecondSelectedRegion)
			{
				SecondSelectedRegion->ToggleSelection();
			}
			SecondSelectedRegion = regionSelected;
			SecondSelectedRegion->ToggleSelection();
		}
		if (FirstSelectedRegion && FirstSelectedRegion->CanAttackThisRegion(SecondSelectedRegion))
		{
			PlayerHUD->ShowAttackUi(FirstSelectedRegion);
		}
		break;
	case EGamePhase::FortificationPhase:

		if (regionSelected->GetRegionOwner() != this)
			return;
		

	    if(FirstSelectedRegion == regionSelected)
		{
			FirstSelectedRegion->ToggleSelection();
			FirstSelectedRegion = nullptr;
		}
		else if (SecondSelectedRegion == regionSelected)
		{
			SecondSelectedRegion->ToggleSelection();
			SecondSelectedRegion = nullptr;
		}
		else if (!FirstSelectedRegion)
		{
			FirstSelectedRegion = regionSelected;
			FirstSelectedRegion->ToggleSelection();
		}
		else
		{
			if (SecondSelectedRegion)
			{
				SecondSelectedRegion->ToggleSelection();
			}
			SecondSelectedRegion = regionSelected;
			SecondSelectedRegion->ToggleSelection();
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

void APlayerCharacter::StartDeploymentPhase(int32 unitsToDeploy)
{
	CurrentPhase = EGamePhase::DeploymentPhase;
	CurrentUnitsToDeploy = unitsToDeploy;
	ChangeGamePhase.Execute(CurrentPhase);
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
