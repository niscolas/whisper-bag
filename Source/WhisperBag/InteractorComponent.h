#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "InteractorComponent.generated.h"

class ADialogueTrigger;
class APickableItem;
class UInventoryComponent;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FNewDialogueTriggered, TArray<FText>, DialogueLines, ADialogueTrigger *, DialogueTriggerActor);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class WHISPERBAG_API UInteractorComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UInteractorComponent();

    UFUNCTION()
    void Setup(UInventoryComponent *InInventoryComponent);

    UFUNCTION()
    void TryInteract();

private:
    UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess))
    FNewDialogueTriggered NewDialogueTriggered;

    UPROPERTY()
    USkeletalMeshComponent *OwnerMesh;

    UPROPERTY()
    UInventoryComponent *InventoryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    APickableItem *PossiblePickableItem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    ADialogueTrigger *PossibleDialogueTrigger;

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnActorBeginOverlap(AActor *OverlappedActor, AActor *OtherActor);

    UFUNCTION()
    void OnActorEndOverlap(AActor *OverlappedActor, AActor *OtherActor);
};
