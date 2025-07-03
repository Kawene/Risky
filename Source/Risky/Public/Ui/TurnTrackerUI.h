#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnTrackerUI.generated.h"


UCLASS()
class RISKY_API UTurnTrackerUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PhaseInformation;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NumberInformation;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* PhaseIcon;

protected:
	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* DeploymentIcon;
	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* AttackIcon;
	UPROPERTY(EditAnywhere, Category = "Icons")
	class UTexture2D* FortificationIcon;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UPlayerInformationUI* PlayerInformation;

	void DeploymentInformation(int32 amountToDeploy);

	void AttackInformation();

	void FortificationInformation();
};
