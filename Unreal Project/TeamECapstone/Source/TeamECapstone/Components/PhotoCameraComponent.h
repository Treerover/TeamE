// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhotoCameraComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMECAPSTONE_API UPhotoCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhotoCameraComponent();

	// Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UStaticMeshComponent* CameraMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class USceneCaptureComponent2D* CaptureComponent;

	// Function to capture and process the photo
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CapturePhoto();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	TArray<UTexture2D*> PictureSlots;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	int32 MaxPictureSlots = 20;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int SlotIndex = 0;
};
