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
		OwnedSelectedRegion->DeployUnits(unitsToDeploy);
		if (CurrentUnitsToDeploy == 0)
		{
			FinishedCurrentPhase();
		}
	}
}

void APlayerCharacter::AttackSelectedRegion(int32 attackerAmount)
{
	if (OwnedSelectedRegion && EnemySelectedRegion)
	{
		bool regionCaptured = Super::CombatRegion(OwnedSelectedRegion, EnemySelectedRegion, attackerAmount);
		AttackStep.Execute(regionCaptured);
	}
}

void APlayerCharacter::FinishedCurrentPhase()
{
	Super::FinishedCurrentPhase();

	if (CurrentPhase == EGamePhase::FortificationPhase)
	{
		CurrentPhase = EGamePhase::NotCurrentTurn;
		ChangeGamePhase.Execute(CurrentPhase);
	}
}

void APlayerCharacter::TransferAmount(int32 amount)
{
	TransferUnits(OwnedSelectedRegion, EnemySelectedRegion, amount);
	EnemySelectedRegion = nullptr;
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

void APlayerCharacter::SelectRegion(ARegion* regionSelected)
{
	if (regionSelected->GetRegionOwner() == this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Selected Own region"));
		OwnedSelectedRegion = regionSelected;

		switch (CurrentPhase)
		{
		case EGamePhase::NotCurrentTurn:
			break;
		case EGamePhase::DeploymentPhase:
			PlayerHUD->ShowDeployUi(CurrentUnitsToDeploy);
			break;
		case EGamePhase::AttackPhase:
			if (OwnedSelectedRegion->CanAttackThisRegion(EnemySelectedRegion))
			{
				PlayerHUD->ShowAttackUi(OwnedSelectedRegion);
			}
			break;
		case EGamePhase::FortificationPhase:
			PlayerHUD->ShowFortificationUi();
			break;
		default:
			break;
		}

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Enemy detected"));
		EnemySelectedRegion = regionSelected;

		switch (CurrentPhase)
		{
		case EGamePhase::AttackPhase:
			if (OwnedSelectedRegion && OwnedSelectedRegion->CanAttackThisRegion(EnemySelectedRegion))
			{
				PlayerHUD->ShowAttackUi(OwnedSelectedRegion);
			}
			break;
		default:
			break;
		}
	}
}
