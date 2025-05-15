#pragma once

#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "WhisperBag/MiscTypes.h"
#include "InventoryComponent.generated.h"

class AItem3dManager;
class APickableItem;
class UInventoryItem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class WHISPERBAG_API UInventoryComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UInventoryComponent();

    UFUNCTION(BlueprintCallable)
    bool AddItem(APickableItem *PickableItem);

    UFUNCTION(BlueprintCallable)
    bool Add2dItem(EItemType Type, UTexture2D *Icon);

    UFUNCTION(BlueprintCallable)
    bool Add3dItem(EItemType Type, AActor *ItemInstance);

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<EItemType, UInventoryItem *> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    int32 MaxSlots = 4;

    UPROPERTY(Transient)
    AItem3dManager *CachedItem3dManager;

    AItem3dManager *GetItem3dManager();
};
