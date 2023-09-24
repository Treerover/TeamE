// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Foid.generated.h"

UCLASS()
class TEAMECAPSTONE_API AFoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float RotateRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	class ASwarmLeader* MySwarmLeader;


	// Swarm Stuff that is not needed right now, but we cna try to make it work later

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	float NeighborRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	float FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	FVector Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	FVector Coherence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	FVector Avoidance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	int NeighborCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	float AvoidDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Not_used")
	class AFishSwarm* MySwarm;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Swarm Stuff that is not needed right now, but we cna try to make it work later

	void SetSwarm(AFishSwarm* swarm);

	void SwarmMovement();
};
