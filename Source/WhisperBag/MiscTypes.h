#pragma once

#include "CoreMinimal.h"
#include "MiscTypes.generated.h"

UENUM()

enum class EItemType : uint8 { StrangeBottle, WeirdShovel, OldKey, RustyCoin };

UENUM()

enum class EItemDimensionType : uint8 { Item2D, Item3D };
