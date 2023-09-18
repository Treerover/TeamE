// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

UCLASS()
class TEAMECAPSTONE_API AChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chests")
		class UBoxComponent* ChestHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chests")
		class UStaticMeshComponent* ChestMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chests")
		class UMaterial* ChestMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chests")
		class USphereComponent* PickupRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bCanLoot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
