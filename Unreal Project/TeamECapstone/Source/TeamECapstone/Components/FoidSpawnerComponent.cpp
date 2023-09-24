// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FoidSpawnerComponent.h"
#include "Actors/Foid.h"
#include "Actors/FishSwarm.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UFoidSpawnerComponent::UFoidSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MySwarm = CreateDefaultSubobject<AFishSwarm>(TEXT("Swarm"));
	

	NumberToSpawnAtStart = 10;
	SpawnRadius = 400;
}


// Called when the game starts
void UFoidSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	MySwarm->SetActorLocation(GetOwner()->GetActorLocation());
	

	SpawnFoids();
	
}


// Called every frame
void UFoidSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFoidSpawnerComponent::SpawnFoids()
{
	FRandomStream RandomStream(FMath::Rand());

	//if (FoidTemplate)
	{
		UWorld* world = GetWorld();

		for (int i = 0; i < NumberToSpawnAtStart; i++)
		{
			// Generate a random pitch, yaw, and roll in the specified range
			float MinPitch = -90.0f; // Minimum pitch angle in degrees
			float MaxPitch = 90.0f;  // Maximum pitch angle in degrees

			float MinYaw = -180.0f; // Minimum yaw angle in degrees
			float MaxYaw = 180.0f;  // Maximum yaw angle in degrees

			float MinRoll = -180.0f; // Minimum roll angle in degrees
			float MaxRoll = 180.0f;  // Maximum roll angle in degrees

			FRotator RandomRotation = FRotator(FMath::RandRange(MinPitch, MaxPitch), FMath::RandRange(MinYaw, MaxYaw), FMath::RandRange(MinRoll, MaxRoll));

			FVector randomPointInsideCircle = RandomStream.VRand() * FMath::RandRange(0.0f, 1.0f);

			FVector pos = GetOwner()->GetActorLocation() + randomPointInsideCircle * SpawnRadius;

			FActorSpawnParameters spawnParams;
			spawnParams.Instigator = GetOwner()->GetInstigator();
			spawnParams.Owner = GetOwner();

			AFoid* foid = world->SpawnActor<AFoid>(pos, RandomRotation, spawnParams);
			GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Green, "Foid created", true);
			MySwarm->AddFoid(foid);
			MySwarm->Target = GetOwner();
		}
	}
}

