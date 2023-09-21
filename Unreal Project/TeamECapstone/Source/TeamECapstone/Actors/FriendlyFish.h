// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FriendlyFish.generated.h"


UENUM()
enum class FriendlyFishState
{
	Idle,
	Patrolling,
	Flee,
	NumStates
};


UCLASS()
class TEAMECAPSTONE_API AFriendlyFish : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFriendlyFish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "1_Fish_Specs")
	class ATeamECapstoneCharacter* DiverReference;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "1_Fish_Specs")
	FVector DiverLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	FriendlyFishState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	float RotateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	float ObliviousDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	float FleeDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	TArray<AActor*> PatrolWaypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	int WaypointIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Fish_Specs")
	float IdleTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Idle(float DeltaTime);

	void Patrol(float DeltaTime);

	void SwimAway(float DeltaTime);

	void SetupDiverReference();

	FORCEINLINE void SetStatePatrol() { State = FriendlyFishState::Patrolling; };
	FORCEINLINE void SetStateIdle() { State = FriendlyFishState::Idle; };
	FORCEINLINE void SetStateFlee() { State = FriendlyFishState::Flee; };

};
