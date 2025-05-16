#pragma once

#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "WhisperBag/MiscTypes.h"
#include "InventoryComponent.generated.h"

class AItem3dManager;
class APickableItem;
class UInventoryItem;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class WHISPERBAG_API UInventoryComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UInventoryComponent();

    UFUNCTION(BlueprintCallable)
    bool AddItem(APickableItem *PickableItem);

    UFUNCTION(BlueprintCallable)
    bool RemoveItem(EItemType Type);

    UFUNCTION(BlueprintCallable)

    TArray<UInventoryItem *> GetItemsAsArray() {
        Items.GenerateValueArray(ItemsArray);
        return ItemsArray;
    }

private:
    UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess))
    FInventoryUpdated InventoryUpdated;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<EItemType, UInventoryItem *> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    int32 MaxSlots = 4;

    UPROPERTY(Transient)
    AItem3dManager *CachedItem3dManager;

    UFUNCTION(BlueprintCallable)
    bool Add2dItem(EItemType Type, UTexture2D *Icon, AActor *ItemInstance);

    UFUNCTION(BlueprintCallable)
    bool Add3dItem(EItemType Type, AActor *ItemInstance);

    UPROPERTY()
    TArray<UInventoryItem *> ItemsArray;

    AItem3dManager *GetItem3dManager();
};
