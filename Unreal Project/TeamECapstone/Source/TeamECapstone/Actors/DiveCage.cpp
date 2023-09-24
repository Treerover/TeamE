// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DiveCage.h"
#include "Components/BoxComponent.h"

// Sets default values
ADiveCage::ADiveCage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	CollisionBox = CreateDefaultSubobject <UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(Mesh);
	CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));


}

// Called when the game starts or when spawned
void ADiveCage::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalLocation = GetActorLocation();
}

void ADiveCage::LowerCage()
{

	SetActorLocation(GetActorLocation() + FVector(0, 0, -3));

}

void ADiveCage::RaiseCage()
{
	if (GetActorLocation().Z < OriginalLocation.Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0, 0, 3));
	}
}

// Called every frame
void ADiveCage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

