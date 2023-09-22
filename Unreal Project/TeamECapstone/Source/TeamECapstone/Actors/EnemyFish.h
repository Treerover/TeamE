// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFish.generated.h"

UENUM(BlueprintType)
enum class EnemyFishState
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
class TEAMECAPSTONE_API AEnemyFish : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFish();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_Fish")
		class ATeamECapstoneCharacter* DiverReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_Fish")
		FVector DiverLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy_Fish")
		EnemyFishState AState;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Idle(float DeltaTime);

	void Patrol(float DeltaTime);

	void SwimAway(float DeltaTime);

	void AttackDiver(float DeltaTime);

	void Sleep(float DeltaTime);

	void Feed(float DeltaTime);

	//If fish is more camoed then others, it can choose to hide
	void Hide(float DeltaTime);

	void SetupDiverReference();

	FORCEINLINE void SetStatePatrol() { AState = EnemyFishState::Patrolling; };
	FORCEINLINE void SetStateIdle() { AState = EnemyFishState::Idle; };
	FORCEINLINE void SetStateFlee() { AState = EnemyFishState::Flee; };
	FORCEINLINE void SetStateAttack() { AState = EnemyFishState::Sleep; };
	FORCEINLINE void SetStateFeed() { AState = EnemyFishState::Feed; };
	FORCEINLINE void SetStateSleep() { AState = EnemyFishState::Attack; };
	FORCEINLINE void SetStateSleep() { AState = EnemyFishState::Hide; };

};
