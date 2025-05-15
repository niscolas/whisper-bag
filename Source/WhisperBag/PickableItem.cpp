#include "PickableItem.h"

APickableItem::APickableItem() {
    PrimaryActorTick.bCanEverTick = false;
}

void APickableItem::BeginPlay() {
    Super::BeginPlay();
}
