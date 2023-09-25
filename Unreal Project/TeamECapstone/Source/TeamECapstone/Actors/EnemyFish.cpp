// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyFish.h"

#include "TeamECapstoneCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyFish::AEnemyFish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Collision Box Setup
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(10, 30, 10));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionProfileName("BlockAll");
	CollisionBox->SetSimulatePhysics(false);

	// Mesh Setup
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Fish Mesh"));
	Mesh->SetupAttachment(CollisionBox);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionProfileName("BlockAll");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;
	Mesh->SetStaticMesh(Asset);
	Mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	SetStateIdle();

	MoveSpeed = 1.0f;
	RotateSpeed = 6.0f;
	ObliviousDistance = 1000.0f;
	FleeDistance = 2000.0f;
	AttackDistance = 100.0f;
	IdleTime = 2.0f;

}

// Called when the game starts or when spawned
void AEnemyFish::BeginPlay()
{
	Super::BeginPlay();

	SetupDiverReference();
	
}

// Called every frame
void AEnemyFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//switch (AState) {
	//case EnemyFishState::Idle:
	//	Idle(DeltaTime);
	//	break;
	//case EnemyFishState::Patrolling:
	//	Patrol(DeltaTime);
	//	break;
	//case EnemyFishState::Flee:
	//	SwimAway(DeltaTime);
	//	break;
	//case EnemyFishState::Attack:


	//	break;
	//case EnemyFishState::Feed:
	//	break;

	//case EnemyFishState::Sleep:



	//	break;

	//}
	
}

void AEnemyFish::Idle(float DeltaTime)
{
	FTimerHandle idleTimerHandle;
	UWorld* world = GetWorld();

	world->GetTimerManager().SetTimer(idleTimerHandle, this, &AEnemyFish::SetStatePatrol, IdleTime, false);
}

void AEnemyFish::Patrol(float DeltaTime)
{

	// Check if Diver is close by, if too close, set State to Flee
	FVector newPos = FVector(0, 0, 0);
	FVector fishLocation = GetActorLocation();

	if ((fishLocation - DiverLocation).Length() < ObliviousDistance)
	{
		SetStateFlee();
		return;
	}

	//Later Attack use
	/*if ((fishLocation - DiverLocation).Length() < ObliviousDistance && Diver.GetStress() < 90)
	{
		SetStateAttack();
		return;
	}*/

	//If Going to Feed Waypoint.


	//If Going to Sleep Waypoint.



	// Move to next Patrol Point
	FVector nextWaypointLocation = PatrolWaypoints[WaypointIndex]->GetActorLocation();
	newPos += FMath::Lerp(fishLocation, nextWaypointLocation, MoveSpeed * DeltaTime);

	if ((fishLocation - nextWaypointLocation).Length() < 10.0f)
	{
		WaypointIndex++;
		WaypointIndex = WaypointIndex % PatrolWaypoints.Num();
	}

	SetActorLocation(newPos);

	// Rotates towards next waypoint
	FVector direction = (nextWaypointLocation - fishLocation).GetSafeNormal();
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), UKismetMathLibrary::MakeRotFromX(direction), DeltaTime, RotateSpeed);

	SetActorRotation(newRot);
}

void AEnemyFish::SwimAway(float DeltaTime)
{
	FVector newPos = FVector(0, 0, 0);
	FVector fishLocation = GetActorLocation();

	FVector directionAwayFromDiver = (DiverLocation - fishLocation).GetSafeNormal();

	newPos += FMath::Lerp(fishLocation, DiverLocation + directionAwayFromDiver * 300, MoveSpeed * DeltaTime);
	SetActorLocation(newPos);

	// Rotates towards next waypoint
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), UKismetMathLibrary::MakeRotFromX(directionAwayFromDiver), DeltaTime, RotateSpeed);

	SetActorRotation(newRot);

	if ((fishLocation - DiverLocation).Length() < FleeDistance)
	{
		SetStateIdle();
		return;
	}
}

void AEnemyFish::AttackDiver(float DeltaTime)
{
	FVector newPos = FVector(0, 0, 0);
	FVector fishLocation = GetActorLocation();

	FVector directionToDiver = (DiverLocation - fishLocation).GetSafeNormal();


	// Rotates towards next waypoint
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), UKismetMathLibrary::MakeRotFromX(directionToDiver), DeltaTime, RotateSpeed);

	SetActorRotation(newRot);

	if ((fishLocation - DiverLocation).Length() < AttackDistance)
	{
		SetStateIdle();
		return;
	}
}

void AEnemyFish::Sleep(float DeltaTime)
{
	// When near Den will swim in and be idle and lowering oblivious distance 

	//idle 
	SetStateIdle();

	//when leaving give speed boost
}

void AEnemyFish::Feed(float DeltaTime)
{
	// When near Den will swim in and be idle and lowering oblivious distance 
	SetStateIdle();
}

void AEnemyFish::Hide(float DeltaTime)
{
	//raycast below the fish to see how far down it can swim

	//make it swim down to the bottom

	//Become idle until swimmer leaves the area or takes a photo.
	
	//When photo is taken, based on agressivness, flee or attack.

}

void AEnemyFish::SetupDiverReference()
{
	for (TObjectIterator<ATeamECapstoneCharacter> Itr; Itr; ++Itr)
	{
		DiverReference = *Itr;
	}

	if (DiverReference)
	{
		DiverLocation = DiverReference->GetActorLocation();
	}
}

