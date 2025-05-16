#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WhisperBag/MiscTypes.h"
#include "InventoryItem.generated.h"

UCLASS(Blueprintable)

class WHISPERBAG_API UInventoryItem : public UObject {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemDimensionType DimensionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D *Icon2dTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTextureRenderTarget2D *Icon3dRenderTarget;
};
