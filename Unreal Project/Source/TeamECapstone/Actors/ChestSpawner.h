// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChestSpawner.generated.h"

UCLASS()
class TEAMECAPSTONE_API AChestSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChestSpawner();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChestSpawner")
		class UBoxComponent* ChestSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chests")
		class TSubclassOf<AActor> ChestClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	FVector SpawnRange;
	UPROPERTY()
	int ChestAmount;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnChests();

};
