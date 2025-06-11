// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_LevelData.generated.h"

UCLASS()
class RISKY_API UGI_LevelData : public UGameInstance
{
	GENERATED_BODY()


	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfAI = 1;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 StartingAmount = 0;
};
