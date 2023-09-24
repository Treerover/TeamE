// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PCTerminal.h"

// Sets default values
APCTerminal::APCTerminal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	bIsInPc = false;

	Tags.Add("Interactable");
}

// Called when the game starts or when spawned
void APCTerminal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCTerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APCTerminal::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted with PC Terminal"));

}

