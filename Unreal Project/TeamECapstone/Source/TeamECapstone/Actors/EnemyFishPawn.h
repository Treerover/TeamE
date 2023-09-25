// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyFishPawn.generated.h"

UENUM(BlueprintType)
enum class EnemyPawnFishState
{
	Idle,
	Patrolling,
	Flee,
	Attack,
	Feed,
	Sleep,
	Hide,
	NumStates
};



UCLASS()
class TEAMECAPSTONE_API AEnemyFishPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyFishPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_Fish")
		class ATeamECapstoneCharacter* DiverReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_Fish")
		FVector DiverLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		EnemyPawnFishState AState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		float RotateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		float ObliviousDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		float FleeDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		TArray<AActor*> PatrolWaypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		int WaypointIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		float IdleTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Idle(float DeltaTime);

	void Patrol(float DeltaTime);

	void SwimAway(float DeltaTime);

	void AttackDiver(float DeltaTime);

	void Sleep(float DeltaTime);

	void Feed(float DeltaTime);

	//If fish is more camoed then others, it can choose to hide
	void Hide(float DeltaTime);

	void SetupDiverReference();

	FORCEINLINE void SetStatePatrol() { AState = EnemyPawnFishState::Patrolling; };
	FORCEINLINE void SetStateIdle() { AState = EnemyPawnFishState::Idle; };
	FORCEINLINE void SetStateFlee() { AState = EnemyPawnFishState::Flee; };
	FORCEINLINE void SetStateAttack() { AState = EnemyPawnFishState::Sleep; };
	FORCEINLINE void SetStateFeed() { AState = EnemyPawnFishState::Feed; };
	FORCEINLINE void SetStateSleep() { AState = EnemyPawnFishState::Attack; };


};
