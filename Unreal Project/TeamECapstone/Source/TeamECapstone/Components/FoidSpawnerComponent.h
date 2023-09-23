// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FoidSpawnerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMECAPSTONE_API UFoidSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFoidSpawnerComponent();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawner_Specs")
	//TSubclassOf<class Foid*> FoidTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawner_Specs")
	int NumberToSpawnAtStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawner_Specs")
	int SpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Spawner_Specs")
	class AFishSwarm* MySwarm;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnFoids();
};
