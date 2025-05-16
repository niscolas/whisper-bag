#pragma once

#include "CoreMinimal.h"
#include "MiscTypes.generated.h"

UENUM(BlueprintType)

enum class EItemType : uint8 { StrangeBottle, WeirdShovel, OldKey, RustyCoin };

UENUM(BlueprintType)

enum class EItemDimensionType : uint8 { Item2D, Item3D };
