// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "PCTerminal.generated.h"

UCLASS()
class TEAMECAPSTONE_API APCTerminal : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCTerminal();

	// Static mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	// Collision box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		class UBoxComponent* CollisionBox;

	// Called when the player interacts with this object
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
		void Interact() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
