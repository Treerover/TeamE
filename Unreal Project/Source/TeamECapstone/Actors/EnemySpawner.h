// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TEAMECAPSTONE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawn_Specs")
	class UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawn_Specs")
	class TSubclassOf<AActor> Enemy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawn_Specs")
		int NumEnemies;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnEnemies();


};
