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

	virtual void Tick(float DeltaTime) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void StartDeploymentPhase() override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;

	UFUNCTION()
	void OnClickRegion(ARegion* regionSelected);

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void AttackSelectedRegion(int32 attackerAmount);

	void FinishedCurrentPhase() override;

	void TransferAmount(int32 amount);

	void DialogAction(int32 units);

	virtual void  IsCharacterDead() override;

	FChangeGamePhase ChangeGamePhase;

	FAttackStep AttackStep;


	void SetUiOpen(bool isOpen);

	UPROPERTY()
	class AAiCharacter* AiPlayer;

	void TransferTo(bool toPlayer);

	virtual void TurnManagerRef(ATurnManager* tManager) override;

	bool IsCameraMoving() const {
		return CameraMoving;
	};

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	bool CameraZoomedIn;

	UPROPERTY()
	bool CameraMoving;

	FVector CameraTargetLocation;

	float CameraTargetArmLength;

	float PreviousCameraTargetArmLength;


	bool IsUiOpen;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainUI> PlayerHUDClass;

	UPROPERTY()
	class UMainUI* PlayerHUD;

	UPROPERTY()
	class ARegion* FirstSelectedRegion;

	UPROPERTY()
	class ARegion* SecondSelectedRegion;

	UPROPERTY()
	EGamePhase CurrentPhase;

	void DeployUnitsToSelectedRegion(int32 unitsToDeploy);
	void SelectRegion(ARegion** regionToModify, ARegion* regionSelected);
	void DeselectRegion(ARegion** region, bool deZoom = true);

	void ZoomCameraToRegion(ARegion* regionSelected);

	void MoveCameraToRegion(ARegion* regionSelected);

	void DeZoomCamera();

};