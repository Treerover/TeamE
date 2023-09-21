// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pawns/DiveBot.h"
#include "TeamECapstoneCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADiveBot::ADiveBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Collision Box Setup
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(25, 25, 25));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionProfileName("BlockAll");
	CollisionBox->SetSimulatePhysics(false);
	//CollisionBox->SetEnableGravity(false);

	// Mesh Setup
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera Mesh"));
	Mesh->SetupAttachment(CollisionBox);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionProfileName("BlockAll");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;
	Mesh->SetStaticMesh(Asset);
	Mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	HoverDistance = 200.0f;
	Speed = 10.0f;

}

// Called when the game starts or when spawned
void ADiveBot::BeginPlay()
{
	Super::BeginPlay();

	SetupDiverReference();
	
	
}

// Called every frame
void ADiveBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Update the divers location.
	if (DiverReference)
	{
		DiverLocation = DiverReference->GetActorLocation();

		MoveDiveBot(DeltaTime);
		
	}
	
}

// Called to bind functionality to input
void ADiveBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADiveBot::SetupDiverReference()
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

void ADiveBot::MoveDiveBot(float DeltaTime)
{
	// Move towards diver and hover nearby
	FVector newPos = FVector(0, 0, 0);
	FVector botLocation = GetActorLocation();

	if ((botLocation - DiverLocation).Length() > HoverDistance)
	{
		newPos += FMath::Lerp(botLocation, DiverLocation, Speed * DeltaTime);
		SetActorLocation(newPos);
	}

	// Rotates towards diver
	FVector direction = DiverLocation - botLocation;
	FRotator newRot = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(newRot);
}

