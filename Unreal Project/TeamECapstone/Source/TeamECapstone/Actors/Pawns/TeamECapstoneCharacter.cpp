// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamECapstoneCharacter.h"
#include "TeamECapstoneProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Boat.h"
#include <InteractInterface.h>
#include <BoatWheel.h>
#include "PCTerminal.h"
#include "DiveCage.h"
#include "DiveBot.h"
#include <PhotoCameraComponent.h>


//////////////////////////////////////////////////////////////////////////
// ATeamECapstoneCharacter

ATeamECapstoneCharacter::ATeamECapstoneCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create photo camera component
	PhotoCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PhotoCamera"));
	PhotoCamera->SetupAttachment(GetCapsuleComponent());
	PhotoCamera->SetRelativeLocation(FVector(100.f, 0.f, 60.f)); // Position the camera
	PhotoCamera->bUsePawnControlRotation = true;
	PhotoCamera->SetFieldOfView(30.f);

	//// Photo camera component
	//PhotoCameraComponent = CreateDefaultSubobject<UPhotoCameraComponent>(TEXT("PhotoCameraComponent"));



	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ATeamECapstoneCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}



	//Shit that shouldntbe here but its easy for right now
	//Find all actors of cage 
	TArray<AActor*> CageActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADiveCage::StaticClass(), CageActors);
	CageClass = CageActors[0] ? Cast<ADiveCage>(CageActors[0]) : nullptr;

}

//////////////////////////////////////////////////////////////////////////// Input

void ATeamECapstoneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATeamECapstoneCharacter::EndJump);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATeamECapstoneCharacter::StopMove);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::Look);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::Interact);

		//Lower cage
		EnhancedInputComponent->BindAction(LowerCageAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::LowerCage);

		//Raise cage
		EnhancedInputComponent->BindAction(RaiseCageAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::RaiseCage);

		//Take photo
		EnhancedInputComponent->BindAction(TakePhotoAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::TakePhoto);

		//Aim camera
		EnhancedInputComponent->BindAction(AimCameraAction, ETriggerEvent::Triggered, this, &ATeamECapstoneCharacter::StartAimingCamera);

		//Stop aiming
		EnhancedInputComponent->BindAction(AimCameraAction, ETriggerEvent::Completed, this, &ATeamECapstoneCharacter::StopAimingCamera);




	}
	else
	{
		// Handle the case where the player controller is not valid
		UE_LOG(LogTemp, Error, TEXT("Player controller is not valid"));
	}
}

void ATeamECapstoneCharacter::TurnOffWaterWait()
{
	bJustEnteredWater = false;
	GetCharacterMovement()->Velocity = FVector::ZeroVector;
}

void ATeamECapstoneCharacter::TrasitionMovementStates()
{
	bIsSwiming = !bIsSwiming;
	
	if (bIsSwiming)
	{
		GetCharacterMovement()->GravityScale = 0;
		GetWorld()->GetTimerManager().SetTimer(WaterTimer, this, &ATeamECapstoneCharacter::TurnOffWaterWait, 1.7, false);
		bJustEnteredWater = true;
	}
	else
	{
		GetCharacterMovement()->GravityScale = 1;
		GetWorldTimerManager().ClearTimer(StressHandle);
	}
}

void ATeamECapstoneCharacter::IncreaseStress()
{
	StressPrecentage += StressIncreaseRate;
}


void ATeamECapstoneCharacter::Move(const FInputActionValue& Value)
{
	bIsMoving = true;

	// input is a Vector2D

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (!bIsSwiming)
		{
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
		else
		{
			FVector ForwardVelo;
			FVector NewTargetVelocity;

			FVector RightVelo = GetActorRightVector() * 400 * MovementVector.X;

			if (!bJustEnteredWater)
			{
				ForwardVelo = FirstPersonCameraComponent->GetForwardVector() * 400 * MovementVector.Y;
				NewTargetVelocity = ForwardVelo + RightVelo;
			}
			else
			{
				ForwardVelo = GetActorForwardVector() * 400 * MovementVector.Y;
				NewTargetVelocity = ForwardVelo + RightVelo;
				NewTargetVelocity.Z = GetCharacterMovement()->Velocity.Z;
			}


			GetCharacterMovement()->Velocity = FMath::Lerp(GetCharacterMovement()->Velocity, NewTargetVelocity, 0.8);
		}
	}
}

void ATeamECapstoneCharacter::StopMove(const FInputActionValue& Value)
{
	bIsMoving = false;
}

void ATeamECapstoneCharacter::Look(const FInputActionValue& Value)
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

void ATeamECapstoneCharacter::Interact(const FInputActionValue& Value)
{
	// Perform the raycast
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation();
	//End location based off player lookat view
	FVector EndLocation = StartLocation + (GetControlRotation().Vector() * 500.0f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 2.0f);

	//Find all actors of boat class
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoatWheel::StaticClass(), FoundActors);

	//Find all actors of boat class
	TArray<AActor*> FoundActors1;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APCTerminal::StaticClass(), FoundActors1);

	//Find all actors of boat class
	TArray<AActor*> FoundActors2;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADiveBot::StaticClass(), FoundActors2);
	//THIS IS A SHITTY WAY TO DO THIS BUT ITS JUST FOR THE DEMO. THERE WILL BE AN INTERACTABLE OBJECTS PARENT THAT WILL BE INHERITABLE FROM 
	//Line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, QueryParams))
	{
		//Debug message of what hit result is
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Result: %s"), *HitResult.GetActor()->GetName()));

		if (FoundActors.Num() > 0)
		{
			//If hit result is the boat, call interact function
			if (HitResult.GetActor() == FoundActors[0])
			{
				ABoatWheel* Boat = FoundActors[0] ? Cast<ABoatWheel>(FoundActors[0]) : nullptr;
				if (Boat)
				{
					Boat->Interact();
				}
			}
			//If hit result is the boat, call interact function
			if (HitResult.GetActor() == FoundActors1[0])
			{
				APCTerminal* PC = FoundActors1[0] ? Cast<APCTerminal>(FoundActors1[0]) : nullptr;
				if (PC)
				{
					PC->Interact();
					bIsInTerminal = true;
				}
				
			}

			//If hit result is the boat, call interact function
			if (HitResult.GetActor() == FoundActors2[0])
			{
				ADiveBot* bot = FoundActors2[0] ? Cast<ADiveBot>(FoundActors2[0]) : nullptr;
				if (bot)
				{
					bot->Interact();
				}
			}
		}

	}

}

void ATeamECapstoneCharacter::StartAimingCamera(const FInputActionValue& Value)
{
	////Take control of photo camera	
	FirstPersonCameraComponent->Deactivate();
	PhotoCamera->Activate();
	bIsAimingCamera = true;
}

void ATeamECapstoneCharacter::StopAimingCamera(const FInputActionValue& Value)
{
	////Give control back to player
	FirstPersonCameraComponent->Activate();
	PhotoCamera->Deactivate();
	bIsAimingCamera = false;
}

void ATeamECapstoneCharacter::TakePhoto(const FInputActionValue& Value)
{
//Take photo
	if (bIsAimingCamera)
	{
		/*PhotoCameraComponent->CapturePhoto();*/
	}
}


void ATeamECapstoneCharacter::LowerCage()
{
	CageClass->LowerCage();
}

void ATeamECapstoneCharacter::RaiseCage()
{
	CageClass->RaiseCage();
}

void ATeamECapstoneCharacter::Jump()
{
		Super::Jump();
}

void ATeamECapstoneCharacter::EndJump()
{
	if (!bIsSwiming)
	{
		Super::StopJumping();
	}
}

void ATeamECapstoneCharacter::Tick(float delta)
{
	Super::Tick(delta);

	if (!bIsMoving && bIsSwiming)
	{
		FVector NewVelocity = GetCharacterMovement()->Velocity - ((GetCharacterMovement()->Velocity / 1.2) * delta);

		NewVelocity.Z = GetCharacterMovement()->Velocity.Z;

		GetCharacterMovement()->Velocity = NewVelocity;
	}

	if (!bIsMovingZ && bIsSwiming)
	{
		double NewZVelocity = GetCharacterMovement()->Velocity.Z - ((GetCharacterMovement()->Velocity / 1.2) * delta).Z;

		GetCharacterMovement()->Velocity.Z = NewZVelocity;
	}

	if (bIsSwiming)
	{
		if (!GetWorldTimerManager().IsTimerActive(StressHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(StressHandle, this, &ATeamECapstoneCharacter::IncreaseStress, TimeToApplyStress, false);
		}
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Orange,"StressLevel: " + FString::SanitizeFloat(StressPrecentage) + "%");
	}
}

void ATeamECapstoneCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ATeamECapstoneCharacter::GetHasRifle()
{
	return bHasRifle;
}