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

	void ShowAttackUi(class ARegion* region, int32 enemyCount, FColor enemyColor);

	void ToggleVisibilityPauseUi();

	void ToggleVisibilityScoreboardUi();

	void ShowVictoryUi();

	void ShowDefeatUi();

	void CloseUnitsUi();

	void CloseAttackUi();

	void CloseCurrentUi();

	void UiHasClosed();

	void ButtonVisibility(bool visible);


	UFUNCTION(BlueprintCallable)
	bool IsUiOpen() const { return UiOpen; };


private:

	TArray<class AProvince*> Provinces;

	bool ProvincesDetails = false;

	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* InteractButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ProvinceButton;

	UFUNCTION()
	void OnButtonClick();

	UFUNCTION()
	void OnGamePhaseChange(EGamePhase gamePhase);

	UFUNCTION()
	void ToggleProvincesDetails();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUnitsDialogUI> UnitsHUDClass;

	UPROPERTY()
	class UUnitsDialogUI* UnitsDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAttackUI> AttackHUDClass;

	UPROPERTY()
	class UAttackUI* AttackDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPauseUI> PauseHUDClass;

	UPROPERTY()
	class UPauseUI* PauseDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UVictoryUI> VictoryHUDClass;

	UPROPERTY()
	class UVictoryUI* VictoryDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDefeatUI> DefeatHUDClass;

	UPROPERTY()
	class UDefeatUI* DefeatDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreboardUI> ScoreboardHUDClass;

	UPROPERTY()
	class UScoreboardUI* ScoreboardDialog;

	bool UiOpen = false;
};
