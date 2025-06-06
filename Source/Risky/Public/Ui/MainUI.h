#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePhase.h"
#include "MainUI.generated.h"

class ARiskyPlayerController;
class APlayerCharacter;

UCLASS()
class RISKY_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void  NativeConstruct();

	void InitializeUI(APlayerCharacter* player, ARiskyPlayerController* controller);

	void ShowUnitsUi(int32 maxUnit, FText textButton);

	void ShowAttackUi(class ARegion* region, int32 enemyCount);

	void CloseUnitsUi();

	void CloseAttackUi();

	void ButtonVisibility(bool visible);

private:

	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* InteractButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InteractText;

	UFUNCTION()
	void OnButtonClick();

	UFUNCTION()
	void OnGamePhaseChange(EGamePhase gamePhase);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUnitsDialogUI> UnitsHUDClass;

	UPROPERTY()
	class UUnitsDialogUI* UnitsDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAttackUI> AttackHUDClass;

	UPROPERTY()
	class UAttackUI* AttackDialog;
};
