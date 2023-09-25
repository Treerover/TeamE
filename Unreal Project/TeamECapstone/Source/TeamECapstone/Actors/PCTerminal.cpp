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
	USpringArmComponent* playerspringarm;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "DiveCage", ActorsToFind);
	divecagearm = ActorsToFind[0]->GetComponentByClass<USpringArmComponent>();

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(0.0f, 0.0f, 0.0f), FRotator(0,180,0), spawnparams);
	cam->Tags.Add("TerminalCam");
	cam->AttachToComponent(divecagearm, FAttachmentTransformRules::KeepRelativeTransform);
	cam->AddActorWorldTransform(FTransform(FRotator(-30, 0, 0), FVector(-600, 0, 250)));

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(0.0f, 0.0f, 0.0f), FRotator(0, 0, 0), spawnparams);
	cam->Tags.Add("TerminalCam");
	cam->AttachToComponent(divecagearm, FAttachmentTransformRules::KeepRelativeTransform);
	cam->AddActorWorldTransform(FTransform(FRotator(0, 180, 0), FVector(400, 0, 50)));

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(0.0f, 0.0f, 0.0f), FRotator(0, 0, 0), spawnparams);
	cam->Tags.Add("TerminalCam");
	cam->AttachToComponent(divecagearm, FAttachmentTransformRules::KeepRelativeTransform);
	cam->AddActorWorldTransform(FTransform(FRotator(90, 90, 0),FVector(-50,0,-260)));
	

	
	
	//divecagearm->AttachToComponent(ActorsToFind[0]->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	

	cam = GetWorld()->SpawnActor<ACameraActor>(FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
	cam->Tags.Add("TerminalCam");
	playerspringarm = GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentByClass<USpringArmComponent>();
	cam->AttachToComponent(playerspringarm, FAttachmentTransformRules::KeepRelativeTransform);
	
}