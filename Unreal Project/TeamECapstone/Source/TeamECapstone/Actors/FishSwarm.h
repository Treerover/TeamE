// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishSwarm.generated.h"

UCLASS()
class TEAMECAPSTONE_API AFishSwarm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishSwarm();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	TArray<class AFoid*> Swarm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	float NeighborRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	float FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Swarm_Specs")
	float AvoidDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddFoid(AFoid* foid);

};
