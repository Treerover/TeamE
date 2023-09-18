// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Chest.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Components/SphereComponent.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//create chest mesh
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chest Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/ Script / Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	UStaticMesh* Asset = Mesh.Object;
	ChestMesh->SetStaticMesh(Asset);

	//ConstructorHelpers::FObjectFinder<UMaterial>Mat(TEXT("/Script/Engine.Material'/Game/ThirdPerson/Art/ChestMat.ChestMat'"));
	//UMaterial* MatAsset = Mat.Object;
	ChestMesh->SetupAttachment(RootComponent);


	ChestHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest Hitbox"));
	ChestHitbox->SetupAttachment(RootComponent);
	ChestHitbox->SetBoxExtent(FVector(60, 60, 60), false); // may need to change update overlaps

	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("Chest Pickup Range"));
	PickupRange->SetupAttachment(RootComponent);
	PickupRange->SetSphereRadius(300, true); // may need to change update overlaps

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

