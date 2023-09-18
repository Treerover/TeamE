// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemySpawner.h"
#include "Actors/Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumEnemies = 4;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Spawner"));
	RootComponent = SpawnBox;
	SpawnBox->SetBoxExtent(FVector(1000, 1000, 30));



}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnEnemies();


}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);





}

void AEnemySpawner::SpawnEnemies()
{
	FVector SpawnPosition;
	FVector SpawnTest;
	FHitResult hit;
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = GetInstigator();
	spawnParams.Owner = this;

	AEnemy* EnemyTemplate = Cast<AEnemy>(Enemy);
	spawnParams.Template = EnemyTemplate;

	//AEnemy* enemy;
	//static ConstructorHelpers::FObjectFinder enemy(TEXT("Blueprint’ / Game / Characters / YourBP.YourBP"));

	UWorld* world = GetWorld();

	if (Enemy)
	{
		for (int i = 0; i < NumEnemies; i++)
		{
			SpawnPosition = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawnBox->Bounds.BoxExtent);

			if (world->LineTraceSingleByChannel(hit, SpawnPosition, SpawnPosition - FVector(0,0,1000), ECC_WorldStatic, FCollisionQueryParams(), FCollisionResponseParams()))
			{
				EnemyTemplate = world->SpawnActor<AEnemy>(FVector(SpawnPosition.X, SpawnPosition.Y, hit.Location.Z + 50), FRotator(0, 0, 0), spawnParams);
			}
			else
			{
				i--;
			}

		}
	}

}

