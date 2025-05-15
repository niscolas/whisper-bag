#include "Item3dManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

AItem3dManager::AItem3dManager() {
    PrimaryActorTick.bCanEverTick = false;

    SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
    RootComponent = SceneCapture;

    RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("InventoryRenderTarget"));
    RenderTarget->InitAutoFormat(512, 512);

    CurrentRotation = FRotator::ZeroRotator;
}

void AItem3dManager::BeginPlay() {
    Super::BeginPlay();

    InitializeCaptureComponent();
}

void AItem3dManager::InitializeCaptureComponent() {
    if (!SceneCapture || !RenderTarget) {
        return;
    }

    SceneCapture->TextureTarget = RenderTarget;
    SceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;
    SceneCapture->bCaptureEveryFrame = false;
    SceneCapture->bCaptureOnMovement = false;
    SceneCapture->FOVAngle = 45.f;
    SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

    SceneCapture->ShowFlags.SetAmbientOcclusion(true);
    SceneCapture->ShowFlags.SetBloom(true);
}

void AItem3dManager::ManageItem(AActor *Target) {
    if (!Target) {
        return;
    }

    Target->SetActorLocation(GetActorLocation());
}

void AItem3dManager::CaptureItem(AActor *Target) {
    if (!Target || !SceneCapture) {
        return;
    }

    ClearCapture();

    CurrentlyCapturedItem = Target;
    CurrentRotation = FRotator::ZeroRotator;

    SceneCapture->ShowOnlyActors.Add(Target);

    Target->SetActorLocation(GetActorLocation() + GetActorForwardVector() * CaptureDistance);
    Target->SetActorRotation(FRotator::ZeroRotator);

    SceneCapture->CaptureScene();
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
