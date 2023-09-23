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
	class AFishSwarm* MySwarm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float NeighborRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	FVector Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	FVector Coherence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	FVector Avoidance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	int NeighborCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Foid_Specs")
	float AvoidDistance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSwarm(AFishSwarm* swarm);
};
