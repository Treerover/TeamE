// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiveCage.generated.h"

UCLASS()
class TEAMECAPSTONE_API ADiveCage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADiveCage();

	// Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	// Collision box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		class UBoxComponent* CollisionBox;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Lowers the cage into the water
	UFUNCTION(BlueprintCallable, Category = "1_Dive Cage")
		void LowerCage();

	// Raises the cage out of the water
	UFUNCTION(BlueprintCallable, Category = "1_Dive Cage")
		void RaiseCage();

	// Original location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Dive Cage")
		FVector OriginalLocation;
};
