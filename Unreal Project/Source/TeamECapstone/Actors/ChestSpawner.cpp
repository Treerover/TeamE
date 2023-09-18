// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ChestSpawner.h"
#include "Actors/Chest.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AChestSpawner::AChestSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestSpawner = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest Spawner"));
	ChestSpawner->SetBoxExtent(FVector(5000, 5000, 30));

	

	ChestAmount = 5;
}

// Called when the game starts or when spawned
void AChestSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnRange = ChestSpawner->Bounds.BoxExtent;

	SpawnChests();
}

// Called every frame
void AChestSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChestSpawner::SpawnChests()
{
	FVector SpawnPosition;
	FVector SpawnTest; // used to check if spawn position is over ground
	FHitResult hit;
	FActorSpawnParameters spawn;
	
	AChest* Temp = Cast<AChest>(ChestClass);

	for (int i = 0; i < ChestAmount; i++)
	{
		SpawnPosition = UKismetMathLibrary::RandomPointInBoundingBox(ChestSpawner->Bounds.Origin, SpawnRange);

		if (GetWorld()->LineTraceSingleByChannel(hit, SpawnPosition, FVector(SpawnPosition.X, SpawnPosition.Y, SpawnPosition.Z-1000), ECC_WorldStatic, FCollisionQueryParams(), FCollisionResponseParams()))
		{
			Temp = GetWorld()->SpawnActor<AChest>(FVector(SpawnPosition.X, SpawnPosition.Y, hit.Location.Z + 50), FRotator(0,0,0), spawn);
			
		}
		else
		{
			i--;
		}

	}

}

