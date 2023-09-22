// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FriendlyFish.h"
#include "TeamECapstoneCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFriendlyFish::AFriendlyFish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Collision Box Setup
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(25, 25, 25));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionProfileName("BlockAll");
	CollisionBox->SetSimulatePhysics(false);

	// Mesh Setup
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fish Mesh"));
	Mesh->SetupAttachment(CollisionBox);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionProfileName("BlockAll");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;
	Mesh->SetStaticMesh(Asset);
	Mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	SetStateIdle();
	
	MoveSpeed = 0.2f;
	RotateSpeed = 6.0f;
	ObliviousDistance = 1000.0f;
	FleeDistance = 5000.0f;
	IdleTime = 0.1f;
}

// Called when the game starts or when spawned
void AFriendlyFish::BeginPlay()
{
	Super::BeginPlay();

	SetupDiverReference();
	
}

// Called every frame
void AFriendlyFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDiverLocation();

	switch (State) {
	case FriendlyFishState::Idle:
		Idle(DeltaTime);
		break;
	case FriendlyFishState::Patrolling:
		Patrol(DeltaTime);
		break;
	case FriendlyFishState::Flee:
		SwimAway(DeltaTime);
		break;
	}

}

void AFriendlyFish::Idle(float DeltaTime)
{
	FTimerHandle idleTimerHandle;
	UWorld* world = GetWorld();

	world->GetTimerManager().SetTimer(idleTimerHandle, this, &AFriendlyFish::SetStatePatrol, IdleTime, false);

}

void AFriendlyFish::Patrol(float DeltaTime)
{
	// Check if Diver is close by, if too close, set State to Flee
	FVector newPos = FVector(0, 0, 0);
	FVector fishLocation = GetActorLocation();

	if ((fishLocation - DiverLocation).Length() < ObliviousDistance)
	{
		SetStateFlee();
		return;
	}

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

void AFriendlyFish::SwimAway(float DeltaTime)
{
	FVector newPos = FVector(0, 0, 0);
	FVector fishLocation = GetActorLocation();

	FVector directionAwayFromDiver = (fishLocation - DiverLocation).GetSafeNormal();

	newPos += FMath::Lerp(fishLocation, DiverLocation + directionAwayFromDiver * FleeDistance, MoveSpeed * DeltaTime);
	SetActorLocation(newPos);

	// Rotates towards next waypoint
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), UKismetMathLibrary::MakeRotFromX(directionAwayFromDiver), DeltaTime, RotateSpeed);

	SetActorRotation(newRot);

	if ((fishLocation - DiverLocation).Length() > FleeDistance)
	{
		SetStateIdle();
		return;
	}

}

void AFriendlyFish::SetupDiverReference()
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

void AFriendlyFish::UpdateDiverLocation()
{
	// Update the divers location.
	if (DiverReference)
	{
		DiverLocation = DiverReference->GetActorLocation();

	}
}
