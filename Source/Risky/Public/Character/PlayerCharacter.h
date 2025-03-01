// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GamePhase.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FChangeGamePhase, EGamePhase);
DECLARE_DELEGATE_OneParam(FAttackStep, bool);

UCLASS(Blueprintable)
class APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void StartDeploymentPhase(int32 unitsToDeploy) override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;

	UFUNCTION()
	void SelectRegion(ARegion* regionSelected);

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void DeployUnitsToSelectedRegion(int32 unitsToDeploy);

	void AttackSelectedRegion(int32 attackerAmount);

	void FinishedCurrentPhase() override;

	void TransferAmount(int32 amount);

	FChangeGamePhase ChangeGamePhase;

	FAttackStep AttackStep;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainUI> PlayerHUDClass;

	UPROPERTY()
	class UMainUI* PlayerHUD;

	UPROPERTY()
	class ARegion* OwnedSelectedRegion;

	UPROPERTY()
	class ARegion* EnemySelectedRegion;

	UPROPERTY()
	EGamePhase CurrentPhase;

};