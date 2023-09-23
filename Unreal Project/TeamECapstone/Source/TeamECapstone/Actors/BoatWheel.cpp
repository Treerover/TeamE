// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BoatWheel.h"
#include "Boat.h"
#include <TeamECapstoneCharacter.h>

// Sets default values
ABoatWheel::ABoatWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoatWheelMesh;

	//Mesh 
	BoatWheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoatMesh"));
	BoatWheelMesh->SetCollisionProfileName(TEXT("Pawn"));
	BoatWheelMesh->SetSimulatePhysics(false);


	Tags.Add("Interactable");
}

// Called when the game starts or when spawned
void ABoatWheel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABoatWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bIsPossessing)
	{
		//Set the location of the player pawn to the location of this actor
		PlayerPawn->SetActorLocation(GetActorLocation() + Offset);
	}
}

void ABoatWheel::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact with BoatWheel"));

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoat::StaticClass(), FoundActors);
	ABoat* Boat = FoundActors[0] ? Cast<ABoat>(FoundActors[0]) : nullptr;

	PlayerPawn = Cast<ATeamECapstoneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerPawn->SetActorEnableCollision(false);

	Boat->PossessBoat();

	bIsPossessing = true;

}
