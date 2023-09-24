// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pawns/DiveBot.h"
#include "TeamECapstoneCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Tags.Add("Interactable");

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
	if (DiverReference && !bIsPossesed)
	{
		DiverLocation = DiverReference->GetActorLocation();

		MoveDiveBot(DeltaTime);
	}
	else if (bIsPossesed)
	{
		if (!bIsMovingBackwards && !bIsMovingForwards)
		{
			TargetVelocity = FVector(0, 0, 0);
			CurrentVelocity = FMath::Lerp(CurrentVelocity, TargetVelocity, 0.01);
		}
		else
		{
			CurrentVelocity = FMath::Lerp(CurrentVelocity, TargetVelocity, 0.07);
		}
		SetActorLocation(GetActorLocation() + CurrentVelocity * DeltaTime);
	}
	
}

// Called to bind functionality to input
void ADiveBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Move forward
		EnhancedInputComponent->BindAction(MoveBotForward, ETriggerEvent::Triggered, this, &ADiveBot::MoveForward);
		//Move backward
		EnhancedInputComponent->BindAction(MoveBotBackward, ETriggerEvent::Triggered, this, &ADiveBot::MoveBackward);
		
		//Stop move forward
		EnhancedInputComponent->BindAction(MoveBotForward, ETriggerEvent::Completed, this, &ADiveBot::StopMoveForward);
		//Stop move backward
		EnhancedInputComponent->BindAction(MoveBotBackward, ETriggerEvent::Completed, this, &ADiveBot::StopMoveBackward);
		
		//UnPossessBoat
		EnhancedInputComponent->BindAction(UnPossessBotAction, ETriggerEvent::Triggered, this, &ADiveBot::UnPossessBot);
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADiveBot::Look);
	}

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

void ADiveBot::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact with DiveBot"));


	PlayerPawn = Cast<ATeamECapstoneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerPawn->SetActorEnableCollision(false);

	PossessBot();

	bIsPossesed = true;
}

void ADiveBot::MoveForward()
{
	FVector ForwardVelo = FirstPersonCameraComponent->GetForwardVector() * 400; 
	TargetVelocity = ForwardVelo;
	bIsMovingForwards = true;
}

void ADiveBot::MoveBackward()
{
	FVector BackwardVelo = FirstPersonCameraComponent->GetForwardVector() * -200;
	TargetVelocity = BackwardVelo;
	bIsMovingBackwards = true;
}

void ADiveBot::StopMoveForward()
{
	bIsMovingForwards = false;
}

void ADiveBot::StopMoveBackward()
{
	bIsMovingBackwards = false;
}

void ADiveBot::PossessBot()
{
	// Get the first player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Ensure we have a valid player controller
	if (PlayerController)
	{
		// Cast to the player pawn
		PlayerPawn = Cast<ATeamECapstoneCharacter>(PlayerController->GetPawn());

		// Ensure we have a valid player pawn
		if (PlayerPawn)
		{
			// Unpossess the current pawn
			PlayerController->UnPossess();

			// Possess the boat pawn
			PlayerController->Possess(this);
		}
		else
		{
			// Handle the case where the player pawn is not valid (e.g., it hasn't been spawned)
			UE_LOG(LogTemp, Error, TEXT("Player pawn is not valid"));
		}
	}
	else
	{
		// Handle the case where the player controller is not valid
		UE_LOG(LogTemp, Error, TEXT("Player controller is not valid"));
	}
}

void ADiveBot::UnPossessBot()
{
	// Get the first player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->UnPossess();

		PlayerPawn->PossesPlayer();
	}
}

void ADiveBot::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

