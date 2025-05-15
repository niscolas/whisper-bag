#include "PickableItem.h"
#include "Components/SphereComponent.h"
#include "UObject/UnrealNames.h"

APickableItem::APickableItem() {
    PrimaryActorTick.bCanEverTick = false;

    SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
    SphereCollider->SetupAttachment(RootComponent);
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    SphereCollider->SetSphereRadius(50);

    RootComponent = SphereCollider;
}

void APickableItem::BeginPlay() {
    Super::BeginPlay();
}
