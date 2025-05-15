#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "InteractorComponent.generated.h"

class APickableItem;
class UInventoryComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class WHISPERBAG_API UInteractorComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UInteractorComponent();

    UFUNCTION()
    void Setup(UInventoryComponent *InInventoryComponent);

    UFUNCTION()
    void TryPickupItem();

private:
    UPROPERTY()
    USkeletalMeshComponent *OwnerMesh;

    UPROPERTY()
    UInventoryComponent *InventoryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    APickableItem *PossiblePickableItem;

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnActorBeginOverlap(AActor *OverlappedActor, AActor *OtherActor);

    UFUNCTION()
    void OnActorEndOverlap(AActor *OverlappedActor, AActor *OtherActor);
};
