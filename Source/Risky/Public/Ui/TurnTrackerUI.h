#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnTrackerUI.generated.h"


UCLASS()
class RISKY_API UTurnTrackerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PhaseTracker;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* PlayerTracker;
};
