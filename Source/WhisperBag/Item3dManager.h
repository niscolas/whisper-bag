#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item3dManager.generated.h"

class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

UCLASS()

class WHISPERBAG_API AItem3dManager : public AActor {
    GENERATED_BODY()

public:
    AItem3dManager();

    void InitializeCaptureComponent();
    void CaptureItem(AActor *ItemToCapture);
    void ClearCapture();
    void RotateCapturedItem(float YawDelta, float PitchDelta);

    UFUNCTION(BlueprintCallable)
    void ManageItem(AActor *Target);

    UTextureRenderTarget2D *GetRenderTarget() {
        return RenderTarget;
    }

private:
    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Components",
              meta = (AllowPrivateAccess))
    USceneCaptureComponent2D *SceneCapture;

    UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess))
    UTextureRenderTarget2D *RenderTarget;

    UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess))
    float CaptureDistance = 300.f;

    UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess))
    float MinPitch = -30.f;

    UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess))
    float MaxPitch = 30.f;

    AActor *CurrentlyCapturedItem;
    FRotator CurrentRotation;

    virtual void BeginPlay() override;
};
