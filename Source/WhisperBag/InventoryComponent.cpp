#include "InventoryComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "WhisperBag/InventoryItem.h"
#include "WhisperBag/Item3dManager.h"
#include "WhisperBag/MiscTypes.h"

UInventoryComponent::UInventoryComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::Add2DItem(EItemType Type, UTexture2D *Icon) {
    if (Items.Contains(Type)) {
        return false;
    }

    UInventoryItem *NewItem = NewObject<UInventoryItem>(this);

    NewItem->Icon2dTexture = Icon;
    NewItem->DimensionType = EItemDimensionType::Item2D;

    Items.Add(Type, NewItem);

    return true;
}

bool UInventoryComponent::Add3DItem(EItemType Type, AActor *ItemInstance) {
    if (Items.Contains(Type)) {
        return false;
    }

    UInventoryItem *NewItem = NewObject<UInventoryItem>(this);

    AItem3dManager *Item3dManager = GetItem3dManager();
    Item3dManager->ManageItem(ItemInstance);
    Item3dManager->CaptureItem(ItemInstance);

    NewItem->Icon3dRenderTarget = Item3dManager->GetRenderTarget();
    NewItem->DimensionType = EItemDimensionType::Item3D;
    Items.Add(Type, NewItem);

    return true;
}

AItem3dManager *UInventoryComponent::GetItem3dManager() {
    if (!CachedItem3dManager) {
        CachedItem3dManager = Cast<AItem3dManager>(
            UGameplayStatics::GetActorOfClass(GetWorld(), AItem3dManager::StaticClass()));
    }

    return CachedItem3dManager;
}
