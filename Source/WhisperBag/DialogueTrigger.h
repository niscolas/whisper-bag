#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"
#include "DialogueTrigger.generated.h"

class USphereComponent;
class UCineCameraComponent;

UCLASS()

class WHISPERBAG_API ADialogueTrigger : public AActor {
    GENERATED_BODY()

public:
    ADialogueTrigger();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TArray<FText> DialogueLines;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    UCineCameraComponent *DialogueCameraComponent;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    USphereComponent *SphereCollider;
};
