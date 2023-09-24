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

	//TriggerBox for pulling player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		class UBoxComponent* TriggerBox;

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

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AActor* Player = nullptr;
};
