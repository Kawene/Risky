// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropReceptorUI.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API UDropReceptorUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* ReceptorBorder;
	
protected:
	virtual bool NativeOnDrop(const FGeometry& geometry, const FDragDropEvent& dragDropEvent, UDragDropOperation* operation) override;

};
