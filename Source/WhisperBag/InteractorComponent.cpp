#include "InteractorComponent.h"
#include "GameFramework/Actor.h"
#include "WhisperBag/InventoryComponent.h"
#include "WhisperBag/PickableItem.h"

UInteractorComponent::UInteractorComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UInteractorComponent::BeginPlay() {
    Super::BeginPlay();

    GetOwner()->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnActorBeginOverlap);
    GetOwner()->OnActorEndOverlap.AddDynamic(this, &ThisClass::OnActorEndOverlap);
}

void UInteractorComponent::Setup(UInventoryComponent *InInventoryComponent) {
    InventoryComponent = InInventoryComponent;
}

void UInteractorComponent::OnActorBeginOverlap(AActor *OverlappedActor, AActor *OtherActor) {
    if (APickableItem *PickableItem = Cast<APickableItem>(OtherActor)) {
        PossiblePickableItem = PickableItem;
    }
}

void UInteractorComponent::OnActorEndOverlap(AActor *OverlappedActor, AActor *OtherActor) {
    if (OtherActor == PossiblePickableItem) {
        PossiblePickableItem = nullptr;
    }
}

void UInteractorComponent::TryPickupItem() {
    if (!InventoryComponent || !PossiblePickableItem) {
        return;
    }

    InventoryComponent->AddItem(PossiblePickableItem);
}
