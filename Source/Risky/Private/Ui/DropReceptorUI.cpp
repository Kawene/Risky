// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DropReceptorUI.h"
#include "UI/DragUI.h"
#include "Components/Border.h"
#include <Ui/CardUI.h>

bool UDropReceptorUI::NativeOnDrop(const FGeometry& geometry, const FDragDropEvent& dragDropEvent, UDragDropOperation* operation)
{
	Super::NativeOnDrop(geometry, dragDropEvent, operation);

	UDragUI* dragWidget = Cast<UDragUI>(operation);

	if (!IsValid(dragWidget)) {
		return false;
	}

	if (ReceptorBorder->HasAnyChildren())
	{
		Cast<UCardUI>(ReceptorBorder->GetAllChildren()[0])->ReplaceIntoList();
	}

	ReceptorBorder->AddChild(dragWidget->WidgetReference);
	dragWidget->WidgetReference->SetVisibility(ESlateVisibility::Visible);
	return true;
}
