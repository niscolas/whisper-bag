#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhisperBag/MiscTypes.h"
#include "PickableItem.generated.h"

UCLASS()

class WHISPERBAG_API APickableItem : public AActor {
    GENERATED_BODY()

public:
    APickableItem();

    EItemType GetType() {
        return Type;
    }

    EItemDimensionType GetDimensionType() {
        return DimensionType;
    }

    UTexture2D *GetIcon2dTexture() {
        return Icon2dTexture;
    }

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    EItemDimensionType DimensionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    UTexture2D *Icon2dTexture;

    virtual void BeginPlay() override;
};
