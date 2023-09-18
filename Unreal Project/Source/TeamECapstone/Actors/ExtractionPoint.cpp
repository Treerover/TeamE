// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ExtractionPoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AExtractionPoint::AExtractionPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Make the mesh component
	ExtractionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Extraction Mesh"));
	ExtractionMesh->SetupAttachment(RootComponent);

	//Make the collision component
	ExtractionHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Extraction Collision"));
	ExtractionHitbox->SetupAttachment(RootComponent);
	ExtractionHitbox->SetCollisionProfileName("Trigger");
	ExtractionHitbox->SetBoxExtent(FVector(100.0f, 100.0f, 150.0f));
	ExtractionHitbox->SetCollisionProfileName("OverlapAllDynamic");



	ExtractionHitbox->OnComponentBeginOverlap.AddDynamic(this, &AExtractionPoint::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AExtractionPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExtractionPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AExtractionPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{

		//If extraction zone is active, go to next level
		if (bIsActive)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Player has entered the extraction zone and is active"));
			//Go to next level
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Player has entered the extraction zone but is not active"));
			//Nothing happens
		}

		//Go to next level
	}
}