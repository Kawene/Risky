#pragma once

#include "CoreMinimal.h"
#include "AttackResults.generated.h"

USTRUCT(BlueprintType)
struct RISKY_API FAttackResults
{
    GENERATED_BODY()

    UPROPERTY()
    int16 AttackResult1;

    UPROPERTY()
    int16 AttackResult2;

    UPROPERTY()
    int16 AttackResult3;

    UPROPERTY()
    int16 DefenceResult1;

    UPROPERTY()
    int16 DefenceResult2;

    FAttackResults()
        : AttackResult1(0)
        , AttackResult2(0)
        , AttackResult3(0)
        , DefenceResult1(0)
        , DefenceResult2(0)
    {}
};
