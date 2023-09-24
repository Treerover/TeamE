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
	

	SpawnCamera();
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

void APCTerminal::SpawnCamera()
{
	FActorSpawnParameters spawnparams;
	ACameraActor* cam;
	
	TArray<AActor*> ActorsToFind;
	USpringArmComponent* divecagearm;

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(100.0f, 1000.0f, 150.0f), FRotator(0,180,0), spawnparams);
	cam->Tags.Add("TerminalCam");

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(-8000.0f, 1000.0f, 150.0f), FRotator(0, 0, 0), spawnparams);
	cam->Tags.Add("TerminalCam");

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(0, 0, 0), FRotator(0, 180, 0), spawnparams);
	cam->Tags.Add("DiveCam");

	

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "DiveCage", ActorsToFind);
	divecagearm = ActorsToFind[0]->GetComponentByClass<USpringArmComponent>();
	//divecagearm->AttachToComponent(ActorsToFind[0]->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	cam->AttachToComponent(divecagearm, FAttachmentTransformRules::KeepRelativeTransform);
}