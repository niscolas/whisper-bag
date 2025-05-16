#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhisperBag/MiscTypes.h"
#include "Item3dManager.generated.h"

class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

USTRUCT(BlueprintType)

struct FItemCaptureData {
    GENERATED_BODY()

    UPROPERTY()
    UTextureRenderTarget2D *TextureRenderTarget;

    UPROPERTY()
    AActor *Actor;
};

UCLASS()

class WHISPERBAG_API AItem3dManager : public AActor {
    GENERATED_BODY()

public:
    AItem3dManager();

    UFUNCTION(BlueprintCallable)
    void StartContinuousCaptureFor(EItemType Type);

    UFUNCTION(BlueprintCallable)
    void StopContinuousCapture();

    UFUNCTION(BlueprintCallable)
    void RotateCapturedItem(float YawDelta, float PitchDelta);

    void InitializeCaptureComponent();
    UTextureRenderTarget2D *CaptureItem(EItemType Type, AActor *TargetActor);
    void ClearCapture();

private:
    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Components",
              meta = (AllowPrivateAccess))
    USceneCaptureComponent2D *SceneCapture;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    bool IsContinuousCaptureEnabled;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    EItemType ContinuousCaptureTarget;

    UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess))
    TMap<EItemType, FItemCaptureData> RenderTargets;

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
