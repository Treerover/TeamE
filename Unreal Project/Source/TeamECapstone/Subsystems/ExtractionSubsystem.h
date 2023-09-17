// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ExtractionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TEAMECAPSTONE_API UExtractionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public: 
	//Constructor
	UExtractionSubsystem();

	//Called when the game starts
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	//Called when the game ends
	virtual void Deinitialize() override;

	//Starts arming the bomb
	void StartArmingBomb();

	//Updates the arming percent
	void UpdateArmingPercent();

	//Starts the bomb countdown
	void StartBombCountdown();

	//Explode bomb
	void ExplodeBomb();

	//Check if player is in extraction zone
	bool IsPlayerInExtractionZone();

public:
	//If the player is arming the bomb
	bool bIsArming = false;

	//Arming percent handle
	FTimerHandle ArmingPercentTimerHandle;

	//Bomb countdown timer handle
	FTimerHandle BombCountdownTimerHandle;
private:


	 //Percentage before the bomb is armed
	float CurrentArmingPercent = 0.0f;

	//Timer before the bomb explodes	
	float BombTimer = 0.0f;

};
