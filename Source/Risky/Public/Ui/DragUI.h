// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragUI.generated.h"


UCLASS()
class RISKY_API UDragUI : public UDragDropOperation
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;

};
