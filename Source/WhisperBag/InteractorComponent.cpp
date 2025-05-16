#include "InteractorComponent.h"
#include "GameFramework/Actor.h"
#include "WhisperBag/DialogueTrigger.h"
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
    } else if (ADialogueTrigger *DialogueTrigger = Cast<ADialogueTrigger>(OtherActor)) {
        PossibleDialogueTrigger = DialogueTrigger;
    }
}

void UInteractorComponent::OnActorEndOverlap(AActor *OverlappedActor, AActor *OtherActor) {
    if (OtherActor == PossiblePickableItem) {
        PossiblePickableItem = nullptr;
    } else if (OtherActor == PossibleDialogueTrigger) {
        PossibleDialogueTrigger = nullptr;
    }
}

void UInteractorComponent::TryInteract() {
    if (PossibleDialogueTrigger) {
        NewDialogueTriggered.Broadcast(PossibleDialogueTrigger->DialogueLines);
    } else if (InventoryComponent && PossiblePickableItem) {
        InventoryComponent->AddItem(PossiblePickableItem);
    }
}
