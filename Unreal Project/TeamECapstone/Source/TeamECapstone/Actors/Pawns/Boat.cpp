// Fill out your copyright notice in the Description page of Project Settings.


#include "Boat.h"
#include "Actors/BoatWheel.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TeamECapstoneCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABoat::ABoat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Mesh 
	BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoatMesh"));
	RootComponent = BoatMesh;
	BoatMesh->SetCollisionProfileName(TEXT("Pawn"));
	BoatMesh->SetSimulatePhysics(true);

	// Create and attach the spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoatMesh);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // Adjust the location as needed
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, -180.0f));
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 300.0f); // Position the spring arm
	SpringArm->TargetArmLength = 700.0f; // Set the length of the spring arm
	SpringArm->bEnableCameraLag = true; // Enable camera lag
	SpringArm->CameraLagSpeed = 3.0f; // Set camera lag speed
	SpringArm->bEnableCameraRotationLag = true; // Enable camera rotation lag

	// Create and attach the camera
	BoatCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BoatCamera"));
	BoatCamera->SetupAttachment(SpringArm);
	BoatCamera->bUsePawnControlRotation = false; // Disable pawn control over camera rotation
	BoatCamera->SetRelativeRotation(FRotator(0.0f, -20.0f, 0.0f)); // Set the initial camera rotation

	PlayerDrivingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BoatSeat"));
	PlayerDrivingPoint->SetupAttachment(RootComponent);

	//Add interactable tag
	Tags.Add("Interactable");
}

// Called when the game starts or when spawned
void ABoat::BeginPlay()
{
	Super::BeginPlay();
	
}



void ABoat::MoveForward()
{
	//If current speed is less than max speed, accelerate
	if (CurrentSpeed < MaxSpeed)
	{
		bIsAccelerating = true;
		bIsDecelerating = false;
	}
	else
	{
		bIsAccelerating = false;
	}

	// Apply acceleration
	if (bIsAccelerating)
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, MaxSpeed, GetWorld()->GetDeltaSeconds(), Acceleration);
	}

	// Scale the input value by the movement speed
	FVector ForwardVector = GetActorForwardVector();

	// Output current speed as debug msg
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Speed: %f"), CurrentSpeed));

	// Move the boat
	AddActorWorldOffset(-ForwardVector * CurrentSpeed * GetWorld()->GetDeltaSeconds() * MovementSpeed, true);
}

void ABoat::MoveBackward()
{
	//Move backwards slowly
	FVector ForwardVector = GetActorForwardVector();
	AddActorWorldOffset(ForwardVector * 50 * GetWorld()->GetDeltaSeconds() * MovementSpeed/2, true);
}

void ABoat::Decelerate()
{
	bIsDecelerating = true;
	if (CurrentSpeed > 0.0f)
	{
		// Gradually reduce the speed
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.0f, GetWorld()->GetDeltaSeconds(), Deceleration);

		// Scale the input value by the movement speed
		FVector ForwardVector = GetActorForwardVector();

		// Move the boat
		AddActorWorldOffset(-ForwardVector * CurrentSpeed * GetWorld()->GetDeltaSeconds() * MovementSpeed, true);

		// Output current speed as debug msg
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Speed: %f"), CurrentSpeed));
	}
}

void ABoat::TurnRight()
{
	//Turns the boat slowly to the right
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += TurnSpeed * GetWorld()->GetDeltaSeconds();
	SetActorRotation(NewRotation);
}

void ABoat::TurnLeft()
{
	//Turns the boat slowly to the left
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw -= TurnSpeed * GetWorld()->GetDeltaSeconds();
	SetActorRotation(NewRotation);
}

// Called every frame
void ABoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If decelerating is true, decelerate
	if (bIsDecelerating)
	{
		Decelerate();
	}

}



void ABoat::PossessBoat()
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

void ABoat::UnPossessBoat()
{
	// Get the first player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Ensure we have a valid player controller
	if (PlayerController)
	{
		// Store the current location of the player pawn
		//FVector CurrentLocation = PlayerPawn->GetActorLocation();

		// Unpossess the boat pawn
		PlayerController->UnPossess();

		// Possess the player pawn
		PlayerPawn->PossesPlayer();

		PlayerPawn->SetActorLocation(PlayerDrivingPoint->GetComponentLocation());
		MyWheel->PlayerPawn = nullptr;

		// Restore the player character's location
		//Player->SetActorLocation(CurrentLocation);
	}
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Move forward
		EnhancedInputComponent->BindAction(MoveBoatForward, ETriggerEvent::Triggered, this, &ABoat::MoveForward);
		//Decelerate
		EnhancedInputComponent->BindAction(MoveBoatForward, ETriggerEvent::Completed, this, &ABoat::Decelerate);
		//Move backward
		EnhancedInputComponent->BindAction(MoveBoatBackward, ETriggerEvent::Triggered, this, &ABoat::MoveBackward);
		//Turn right
		EnhancedInputComponent->BindAction(TurnBoatRight, ETriggerEvent::Triggered, this, &ABoat::TurnRight);
		//Turn left
		EnhancedInputComponent->BindAction(TurnBoatLeft, ETriggerEvent::Triggered, this, &ABoat::TurnLeft);

		//UnPossessBoat
		EnhancedInputComponent->BindAction(UnPossessBoatAction, ETriggerEvent::Triggered, this, &ABoat::UnPossessBoat);

	}
}


