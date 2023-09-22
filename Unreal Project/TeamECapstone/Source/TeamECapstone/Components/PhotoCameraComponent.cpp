// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PhotoCameraComponent.h"
#include <Engine/SceneCapture2D.h>
#include <Components/SceneCaptureComponent2D.h>
#include <Engine/TextureRenderTarget2D.h>
#include <Engine/Texture2D.h>
#include "Components/StaticMeshComponent.h"
// Sets default values for this component's properties
UPhotoCameraComponent::UPhotoCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    // Initialize the mesh component
    CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));


	// ...
}


void UPhotoCameraComponent::CapturePhoto()
{
    if (GetWorld())
    {
        // Get the player's camera view and capture it as a texture
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            FVector Location;
            FRotator Rotation;
            PlayerController->GetPlayerViewPoint(Location, Rotation);

            // Create a SceneCaptureComponent2D to capture the scene
            USceneCaptureComponent2D* CaptureComponent = NewObject<USceneCaptureComponent2D>(this);
            CaptureComponent->RegisterComponent();
            CaptureComponent->FOVAngle = PlayerController->PlayerCameraManager->GetFOVAngle();
            CaptureComponent->ProjectionType = ECameraProjectionMode::Type::Perspective;
            CaptureComponent->bCaptureEveryFrame = false;
            CaptureComponent->bCaptureOnMovement = false;
            CaptureComponent->bAlwaysPersistRenderingState = true;

            // Configure the capture component settings
            // You can adjust the resolution and other settings as needed
            CaptureComponent->TextureTarget = NewObject<UTextureRenderTarget2D>(this);
            CaptureComponent->TextureTarget->InitAutoFormat(1024, 1024);
            CaptureComponent->TextureTarget->TargetGamma = 1.0f;
            CaptureComponent->TextureTarget->SRGB = 1;
            CaptureComponent->TextureTarget->CompressionSettings = TextureCompressionSettings::TC_Default;

            // Set the location and rotation of the capture component
            CaptureComponent->SetRelativeLocationAndRotation(Location, Rotation);

            // Capture the scene to the render target
            CaptureComponent->CaptureScene();

            // Access the captured texture
            UTextureRenderTarget2D* CapturedTexture = (CaptureComponent->TextureTarget);
            if (CapturedTexture)
            {
                // Call the function to save the captured texture to a picture slot
                SavePhoto(CapturedTexture);
            }

            // Clean up the capture component
            CaptureComponent->UnregisterComponent();
        }
    }
}

void UPhotoCameraComponent::SavePhoto(UTextureRenderTarget2D* Photo)
{
    if (!Photo)
    {
        return;
    }

    // Find the index of the next available slot or the oldest slot to replace
    int32 SlotIndex = 0;
    if (PictureSlots.Num() >= MaxPictureSlots)
    {
        // If we have already filled all slots, replace the oldest picture (the one at index 0)
        SlotIndex = 0;
        // Release the old render target to free memory
        PictureSlots[SlotIndex]->ReleaseResource();
    }
    else
    {
        // If there's still space, use the next available slot
        SlotIndex = PictureSlots.Num();
    }

    PictureSlots[SlotIndex] = Photo;

    // Save the texture to the picture slot
    PictureSlots[SlotIndex]->UpdateResource();


}

// Called when the game starts
void UPhotoCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    for (int32 SlotIndex = 0; SlotIndex < MaxPictureSlots; ++SlotIndex)
    {
        UTextureRenderTarget2D* RenderTarget = NewObject<UTextureRenderTarget2D>(this);
        RenderTarget->InitCustomFormat(1000, 1000, PF_B8G8R8A8, false);
        PictureSlots.Add(RenderTarget);
    }
}


// Called every frame
void UPhotoCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

