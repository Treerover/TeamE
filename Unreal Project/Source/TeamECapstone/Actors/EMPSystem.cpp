// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EMPSystem.h"
#include "Subsystems/ExtractionSubsystem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include <TeamECapstoneCharacter.h>

// Sets default values
AEMPSystem::AEMPSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the Root Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create the Machine Mesh
	EMPMachineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineMesh"));
	EMPMachineMesh->SetupAttachment(RootComponent);

	// Create the Button Mesh
	EMPMachineButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	EMPMachineButtonMesh->SetupAttachment(RootComponent);

	// Create the charge zone mesh
	EMPChargeZoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChargeZoneMesh"));
	EMPChargeZoneMesh->SetupAttachment(RootComponent);


	// Create the Button Collision
	EMPMachineButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonCollision"));
	EMPMachineButtonCollision->SetupAttachment(RootComponent);
	EMPMachineButtonCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// Create the EMP Sphere
	EMPChargeZone = CreateDefaultSubobject<USphereComponent>(TEXT("EMPSphere"));
	EMPChargeZone->SetupAttachment(RootComponent);
	EMPChargeZone->SetSphereRadius(1500.0f);
	EMPChargeZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	EMPChargeZone->OnComponentBeginOverlap.AddDynamic(this, &AEMPSystem::OnEMPChargeZoneBeginOverlap);
	EMPChargeZone->OnComponentEndOverlap.AddDynamic(this, &AEMPSystem::OnEMPChargeZoneEndOverlap);
}

void AEMPSystem::OnButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EMP System Button Clicked"));
	if (ExtractionSubsystem)
	{
		ExtractionSubsystem->StartArmingBomb();
	}
}

void AEMPSystem::SetChargeZoneVisibility(bool bVisible)
{
	EMPChargeZoneMesh->SetVisibility(bVisible);
}

void AEMPSystem::OnEMPChargeZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entered Charge Zone"));
	//Cast to player
	ATeamECapstoneCharacter* PlayerCharacter = Cast<ATeamECapstoneCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			PlayerCharacter->bInExtractionZone = true;
		}
}

void AEMPSystem::OnEMPChargeZoneEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left Charge Zone"));
	//Cast to player
	ATeamECapstoneCharacter* PlayerCharacter = Cast<ATeamECapstoneCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->bInExtractionZone = false;
	}
}

// Called when the game starts or when spawned
void AEMPSystem::BeginPlay()
{
	Super::BeginPlay();

	// Set the charge zone to be invisible
	EMPChargeZoneMesh->SetVisibility(false);

	// Initialize the ExtractionSubsystem
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		ExtractionSubsystem = GameInstance->GetSubsystem<UExtractionSubsystem>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to obtain game instance or subsystem."));
	}
	
}

// Called every frame
void AEMPSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

