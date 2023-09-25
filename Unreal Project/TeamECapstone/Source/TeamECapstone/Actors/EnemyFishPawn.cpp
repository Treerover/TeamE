// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyFishPawn.h"


#include "TeamECapstoneCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemyFishPawn::AEnemyFishPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void AEnemyFishPawn::BeginPlay()
{
	Super::BeginPlay();


	SetupDiverReference();
}

// Called every frame
void AEnemyFishPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UpdateDiverLocation();
}

// Called to bind functionality to input
void AEnemyFishPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyFishPawn::SetupDiverReference()
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
