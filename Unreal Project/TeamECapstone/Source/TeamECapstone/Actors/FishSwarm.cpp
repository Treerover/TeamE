// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FishSwarm.h"
#include "Actors/Foid.h"


// Sets default values
AFishSwarm::AFishSwarm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 1.0f;
	TurnSpeed = 720;
	NeighborRadius = 20;
	FOV = 180;
	AvoidDistance = 20;

}

// Called when the game starts or when spawned
void AFishSwarm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFishSwarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFishSwarm::AddFoid(AFoid* foid)
{
	Swarm.Add(foid);
	foid->SetSwarm(this);
}

