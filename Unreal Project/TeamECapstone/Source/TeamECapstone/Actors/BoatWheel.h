// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "BoatWheel.generated.h"

UCLASS()
class TEAMECAPSTONE_API ABoatWheel : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoatWheel();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
		class UStaticMeshComponent* BoatWheelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
		class UBoxComponent* BoxCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Static mesh



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
		void Interact() override;

	//Player controller
	class ATeamECapstoneCharacter* PlayerPawn;

private:
	//FVector offset
	FVector Offset = FVector(180, 0, 180);
};
