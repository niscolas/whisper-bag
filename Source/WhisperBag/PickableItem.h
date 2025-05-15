#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhisperBag/MiscTypes.h"
#include "PickableItem.generated.h"

class USphereComponent;

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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
    EItemDimensionType DimensionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
    UTexture2D *Icon2dTexture;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    USphereComponent *SphereCollider;

    virtual void BeginPlay() override;
};
