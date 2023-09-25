// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SwarmLeader.h"
#include "Components/FoidSpawnerComponent.h"
#include "Actors/Foid.h"

// Sets default values
ASwarmLeader::ASwarmLeader()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumberToSpawnAtStart = 40;
	SpawnRadius = 100;
}

// Called when the game starts or when spawned
void ASwarmLeader::BeginPlay()
{
	Super::BeginPlay();


	// Spawn Fish at runtime
	FRandomStream RandomStream(FMath::Rand());

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

		FVector randomPointInsideCircle = RandomStream.VRand() * FMath::RandRange(0.3f, 1.0f);

		FVector pos = GetActorLocation() + randomPointInsideCircle * SpawnRadius;

		FActorSpawnParameters spawnParams;
		spawnParams.Instigator = GetInstigator();
		spawnParams.Owner = this;
		if (foidTemplate)
		{
			AFoid* foid = world->SpawnActor<AFoid>(foidTemplate, pos, RandomRotation, spawnParams);
			GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Green, "Foid created", true);
			foid->MySwarmLeader = this;
		}

	}


}

// Called every frame
void ASwarmLeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

