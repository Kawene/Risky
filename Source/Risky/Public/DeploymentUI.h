#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeploymentUI.generated.h"

UCLASS()
class RISKY_API UDeploymentUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* SliderUnits;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* SliderText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DeployButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DeployButtonText;

	UFUNCTION()
	void DeployUnits();

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	
	void ShowPopup(int32 MaxValue);

	virtual void  NativeConstruct();

	class APlayerCharacter* Player;
};
