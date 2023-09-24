// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TeamECapstoneCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ATeamECapstoneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** First person photo camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PhotoCamera;

	///** Photo Camera Component */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UPhotoCameraComponent* PhotoCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Interact Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InteractAction;

	/** Lower Cage Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LowerCageAction;

	/** Raise Cage Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* RaiseCageAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AimCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* TakePhotoAction;
	
public:
	ATeamECapstoneCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	bool bIsInTerminal = false;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Weapon)
	bool bIsAimingCamera = false;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for interact input */
	void Interact(const FInputActionValue& Value);

	/** Called for start aiming camera input */
	void StartAimingCamera(const FInputActionValue& Value);

	/** Called for stop aiming camera input */
	void StopAimingCamera(const FInputActionValue& Value);

	/** Called for taking photo input */
	void TakePhoto(const FInputActionValue& Value);

	/** Called for lower cage input */
	UFUNCTION(BlueprintCallable, Category = Cage)
	void LowerCage();

	/** Called for raise cage input */
	UFUNCTION(BlueprintCallable, Category = Cage)
	void RaiseCage();

	void Jump();
	void EndJump();

	virtual void Tick(float delta) override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	//TSubclass of cage
	class ADiveCage* CageClass;

	void PossesPlayer();

	//Movement stuff --------------------
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		bool bIsSwiming = false, bJustEnteredWater, bIsMoving = false, bIsMovingZ = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float SwimSpeed = 10;

	FTimerHandle WaterTimer;

	/// <summary>
	/// Used to manage the "bJustEnteredWaterBool" used to force the player to dip into the water before allowing them to control the z axis
	/// </summary>
	void TurnOffWaterWait();

public:

	/// <summary>
	/// Called when the player enters/exits water, allows players to change between swiming and walking states
	/// </summary>
	void TrasitionMovementStates();


	// Stress And Health ---------------------

	protected:
		//Defaults
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
			int MaxHealthStates = 4;

		float StressPrecentage = 0;
		int CurrentHelthState = MaxHealthStates;

		//Increase Rates
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
			float StressIncreaseRate = 0.5; // Per SetTime
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
			float TimeToApplyStress = 4; // Time Player needs to be underwater to applay stress

		void IncreaseStress();

		FTimerHandle StressHandle;
};

