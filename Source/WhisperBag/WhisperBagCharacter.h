#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "WhisperBagCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UInteractorComponent;
class UInventoryComponent;
class USpringArmComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)

class AWhisperBagCharacter : public ACharacter {
    GENERATED_BODY()

public:
    AWhisperBagCharacter();

    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }

    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess))
    USpringArmComponent *CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess))
    UCameraComponent *FollowCamera;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Inventory",
              meta = (AllowPrivateAccess))
    UInventoryComponent *InventoryComponent;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Interaction",
              meta = (AllowPrivateAccess))
    UInteractorComponent *InteractorComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
    UInputMappingContext *DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
    UInputAction *JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
    UInputAction *MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
    UInputAction *LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
    UInputAction *InteractAction;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
    virtual void BeginPlay();

    void Move(const FInputActionValue &Value);
    void Look(const FInputActionValue &Value);
    void Interact(const FInputActionValue &Value);
};
