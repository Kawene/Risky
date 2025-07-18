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

	void EscapeAction();

	void TabAction();

	void StartDeploymentPhase() override;

	void StartAttackPhase() override;

	void StartFortificationPhase() override;

	UFUNCTION()
	void OnClickRegion(ARegion* regionSelected);

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	struct FAttackResults* DeclareAttack(int32 attackerAmount);

	int32 ApplyAttackResults(FAttackResults* results);

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

	bool IsCameraControlled() const {
		return CameraMoving || CameraZoomedIn;
	};

	void ShowVictoryScreen();

	void ShowDefeatScreen();

	void SetCameraToSeeMap();

	void DeZoomCamera();

protected:

	UPROPERTY(BlueprintReadOnly)
	class UMainUI* PlayerHUD;

	virtual void AddCard() override;

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

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* CaptureEffectNiagara;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainUI> PlayerHUDClass;

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

	void MoveCameraToPosition(FVector position);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* TurnStartSound;
};