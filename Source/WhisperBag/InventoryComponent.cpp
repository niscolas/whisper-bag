#include "InventoryComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "WhisperBag/InventoryItem.h"
#include "WhisperBag/Item3dManager.h"
#include "WhisperBag/MiscTypes.h"
#include "WhisperBag/PickableItem.h"

UInventoryComponent::UInventoryComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::AddItem(APickableItem *PickableItem) {
    if (!PickableItem || Items.Contains(PickableItem->GetType())) {
        return false;
    }

    if (PickableItem->GetDimensionType() == EItemDimensionType::Item2D) {
        Add2dItem(PickableItem->GetType(), PickableItem->GetIcon2dTexture(), PickableItem);
    } else {
        Add3dItem(PickableItem->GetType(), PickableItem);
    }

    return true;
}

bool UInventoryComponent::RemoveItem(EItemType Type) {
    if (!Items.Contains(Type)) {
        return false;
    }

    Items.Remove(Type);

    return true;
}

bool UInventoryComponent::Add2dItem(EItemType Type, UTexture2D *Icon, AActor *ItemInstance) {
    UInventoryItem *NewItem = NewObject<UInventoryItem>(this);

    NewItem->Type = Type;
    NewItem->Icon2dTexture = Icon;
    NewItem->DimensionType = EItemDimensionType::Item2D;

    Items.Add(Type, NewItem);

    ItemInstance->Destroy();

    InventoryUpdated.Broadcast();

    return true;
}

bool UInventoryComponent::Add3dItem(EItemType Type, AActor *ItemInstance) {
    UInventoryItem *NewItem = NewObject<UInventoryItem>(this);

    AItem3dManager *Item3dManager = GetItem3dManager();
    UTextureRenderTarget2D *RenderTarget = Item3dManager->CaptureItem(Type, ItemInstance);

    NewItem->Type = Type;
    NewItem->Icon3dRenderTarget = RenderTarget;
    NewItem->DimensionType = EItemDimensionType::Item3D;
    Items.Add(Type, NewItem);

    InventoryUpdated.Broadcast();

    return true;
}

AItem3dManager *UInventoryComponent::GetItem3dManager() {
    if (!CachedItem3dManager) {
        CachedItem3dManager = Cast<AItem3dManager>(
            UGameplayStatics::GetActorOfClass(GetWorld(), AItem3dManager::StaticClass()));
    }

    return CachedItem3dManager;
}
