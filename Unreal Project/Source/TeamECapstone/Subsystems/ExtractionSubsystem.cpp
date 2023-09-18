// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ExtractionSubsystem.h"
#include "TeamECapstoneCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/ExtractionPoint.h"
#include "Actors/EMPSystem.h"


UExtractionSubsystem::UExtractionSubsystem()
{
}

void UExtractionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("ExtractionSubsystem Initialized"));
}

void UExtractionSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UE_LOG(LogTemp, Warning, TEXT("ExtractionSubsystem Deinitialized"));
}

void UExtractionSubsystem::StartArmingBomb()
{
	UE_LOG(LogTemp, Warning, TEXT("StartedArmingBomb"));

	//Sets the player to be in the extraction zone by default since theyre clicking the button 
	ATeamECapstoneCharacter* Player = Cast<ATeamECapstoneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->bInExtractionZone = true;

	//Gets the emp machine in the level (should be one)
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMPSystem::StaticClass(), FoundActors);
	AEMPSystem* EMPMachine = Cast<AEMPSystem>(FoundActors[0]);

	if (EMPMachine)
	{
		EMPMachine->SetChargeZoneVisibility(true);
	}

	if (bIsArming == false)
	{
		bIsArming = true;
		//Start enemy spawning

		GetWorld()->GetTimerManager().SetTimer(ArmingPercentTimerHandle, this, &UExtractionSubsystem::UpdateArmingPercent, 1.0f, true, 0.0f);
	}
}


void UExtractionSubsystem::UpdateArmingPercent()
{

	if (bIsArming)
	{
		if (IsPlayerInExtractionZone())
		{
			//Update the progress bar
			CurrentArmingPercent += 2.0f;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ArmingPercent: %f"), CurrentArmingPercent));

			if (CurrentArmingPercent >= 100.0f)
			{
				StartBombCountdown();
			}
		}
	}
}

void UExtractionSubsystem::StartBombCountdown()
{
	bIsArming = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Started Arming")));
	//Start bomb timer
	GetWorld()->GetTimerManager().SetTimer(BombCountdownTimerHandle, this, &UExtractionSubsystem::ExplodeBomb, BombTimer, false);

	//Gets the extraction point in the level (should be one)
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExtractionPoint::StaticClass(), FoundActors);

	//If the extraction point is found, set it to active
	AExtractionPoint* ExtractionPoint = Cast<AExtractionPoint>(FoundActors[0]);
	if (ExtractionPoint)
	{
		ExtractionPoint->bIsActive = true;
	}


	//Enhance enemy spawning

}

void UExtractionSubsystem::ExplodeBomb()
{
	//Explode bomb
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ExplodeBomb")));

	//Kill player
	ATeamECapstoneCharacter* Player = Cast<ATeamECapstoneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->Destroy();
	}
}

bool UExtractionSubsystem::IsPlayerInExtractionZone()
{
	ATeamECapstoneCharacter* Player = Cast<ATeamECapstoneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		if (Player->IsInExtractionZone())
		{
			return true;
		}
		return false;
	}
	return false;
}
