// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DiveBot.generated.h"

UCLASS()
class TEAMECAPSTONE_API ADiveBot : public APawn
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


};
