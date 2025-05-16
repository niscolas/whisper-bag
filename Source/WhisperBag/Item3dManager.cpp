#include "Item3dManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

AItem3dManager::AItem3dManager() {
    PrimaryActorTick.bCanEverTick = false;

    SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
    RootComponent = SceneCapture;

    CurrentRotation = FRotator::ZeroRotator;
}

void AItem3dManager::BeginPlay() {
    Super::BeginPlay();
}

void AItem3dManager::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

    if (!IsContinuousCaptureEnabled) {
        return;
    }

    SceneCapture->CaptureScene();
}

void AItem3dManager::StartContinuousCaptureFor(EItemType Type) {
    IsContinuousCaptureEnabled = true;
    ContinuousCaptureTarget = Type;

    ClearCapture();

    SceneCapture->TextureTarget = RenderTargets[ContinuousCaptureTarget].TextureRenderTarget;
    SceneCapture->ShowOnlyActors.Add(RenderTargets[ContinuousCaptureTarget].Actor);
    CurrentlyCapturedItem = RenderTargets[ContinuousCaptureTarget].Actor;
}

void AItem3dManager::StopContinuousCapture() {
    IsContinuousCaptureEnabled = false;
    ClearCapture();
}

UTextureRenderTarget2D *AItem3dManager::CaptureItem(EItemType Type, AActor *TargetActor) {
    if (!TargetActor || !SceneCapture) {
        return nullptr;
    }

    FItemCaptureData ItemCaptureData;
    ItemCaptureData.TextureRenderTarget = NewObject<UTextureRenderTarget2D>(this);
    ItemCaptureData.Actor = TargetActor;

    RenderTargets.Add(Type, ItemCaptureData);
    RenderTargets[Type].TextureRenderTarget->InitAutoFormat(512, 512);
    SceneCapture->TextureTarget = RenderTargets[Type].TextureRenderTarget;

    ClearCapture();

    CurrentlyCapturedItem = TargetActor;
    CurrentRotation = FRotator::ZeroRotator;

    SceneCapture->ShowOnlyActors.Add(TargetActor);

    TargetActor->SetActorLocation(GetActorLocation() + GetActorForwardVector() * CaptureDistance);
    TargetActor->SetActorRotation(FRotator::ZeroRotator);
    SceneCapture->CaptureScene();

    return RenderTargets[Type].TextureRenderTarget;
}

void AItem3dManager::ClearCapture() {
    if (CurrentlyCapturedItem) {
        SceneCapture->ShowOnlyActors.Remove(CurrentlyCapturedItem);
        CurrentlyCapturedItem = nullptr;
    }
}

void AItem3dManager::RotateCapturedItem(float YawDelta, float PitchDelta) {
    if (!CurrentlyCapturedItem) {
        return;
    }

    CurrentRotation.Yaw += YawDelta;
    CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch + PitchDelta, MinPitch, MaxPitch);

    CurrentlyCapturedItem->SetActorRotation(CurrentRotation);

    SceneCapture->CaptureScene();
}
