#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EEnemyState : int32
{
	Idle UMETA(DisplayName = "Idle"),
	Range UMETA(DisplayName = "Range"),
	Charge UMETA(DisplayName = "Charge"),
	Melee UMETA(DisplayName = "Melee")
};