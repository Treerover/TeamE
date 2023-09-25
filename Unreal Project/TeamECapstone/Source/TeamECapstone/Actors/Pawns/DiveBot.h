// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractInterface.h"
#include "InputActionValue.h"
#include "DiveBot.generated.h"

class UInputComponent;
class USceneComponent;
class UCameraComponent;

UCLASS()
class TEAMECAPSTONE_API ADiveBot : public APawn, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADiveBot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Bot_Specs")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Bot_Specs")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "1_Bot_Specs")
	class ATeamECapstoneCharacter* DiverReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "1_Bot_Specs")
	FVector DiverLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Bot_Specs")
	float HoverDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_Bot_Specs")
	float Speed;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetupDiverReference();

	void MoveDiveBot(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
		void Interact() override;

protected:
	//Possestion of Divebot

		/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveBotForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveBotBackward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* UnPossessBotAction;


	//Player controller
	class ATeamECapstoneCharacter* PlayerPawn;

	void MoveForward();
	void MoveBackward();
	void StopMoveForward();
	void StopMoveBackward();

	bool bIsMovingForwards = false, bIsMovingBackwards = false;

	void PossessBot();
	void UnPossessBot();

	bool bIsPossesed = false;

	void Look(const FInputActionValue& Value);

	FVector TargetVelocity = FVector::ZeroVector, CurrentVelocity = FVector::ZeroVector;

};
