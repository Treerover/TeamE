// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractInterface.h"
#include "Boat.generated.h"



UCLASS()
class TEAMECAPSTONE_API ABoat : public APawn, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
        class UStaticMeshComponent* BoatMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
		class UBoxComponent* BoxCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
        class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
        class UCameraComponent* BoatCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* MoveBoatForward;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* MoveBoatBackward;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* TurnBoatLeft;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* TurnBoatRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	    class UInputAction* UnPossessBoatAction;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
        void Interact() override;

    // Movement
    void MoveForward();
    void MoveBackward();
    void Decelerate();
    void TurnRight();
    void TurnLeft();

    void PossessBoat();
    void UnPossessBoat();

    float TurnSpeed = 35.0f;
    float CurrentSpeed = 0.0f;
    float MaxSpeed = 200.0f;
    float MovementSpeed = 5.0f;
    float Acceleration = 0.5f;
    float Deceleration = 1.0f;

    bool bIsAccelerating = false;
    bool bIsDecelerating = false;
    bool bMoving = false;

    //Player pawn data
    class ATeamECapstoneCharacter* PlayerPawn;
};
