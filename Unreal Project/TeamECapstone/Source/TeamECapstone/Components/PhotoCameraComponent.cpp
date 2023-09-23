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

    CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));

    
	// ...
}


void UPhotoCameraComponent::CapturePhoto()
{

}




// Called when the game starts
void UPhotoCameraComponent::BeginPlay()
{
	Super::BeginPlay();
    EPixelFormat PixelFormat = EPixelFormat::PF_B8G8R8A8;
	// ...
    for (int32 SlotIndex1 = 0; SlotIndex1 < MaxPictureSlots; ++SlotIndex1)
    {
        UTexture2D* RenderTarget = NewObject<UTexture2D>(this);
        PictureSlots.Add(RenderTarget);
    }
}


// Called every frame
void UPhotoCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

