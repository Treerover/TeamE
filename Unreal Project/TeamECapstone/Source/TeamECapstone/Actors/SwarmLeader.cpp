// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SwarmLeader.h"
#include "Components/FoidSpawnerComponent.h"

#include "Components/SceneComponent.h"

// Sets default values
ASwarmLeader::ASwarmLeader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Location"));
	SetRootComponent(SpawnLocation);

	SpawningComponent = CreateDefaultSubobject<UFoidSpawnerComponent>(TEXT("Spawner"));
	

}

// Called when the game starts or when spawned
void ASwarmLeader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwarmLeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

