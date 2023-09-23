// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwarmLeader.generated.h"

UCLASS()
class TEAMECAPSTONE_API ASwarmLeader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwarmLeader();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_SwarmLeader_Specs")
	class USceneComponent* SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_SwarmLeader_Specs")
	class UFoidSpawnerComponent* SpawningComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
