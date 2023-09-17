// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EMPSystem.generated.h"

UCLASS()
class TEAMECAPSTONE_API AEMPSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEMPSystem();

	// Mesh for the EMP Machine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMP Machine")
		class UStaticMeshComponent* EMPMachineMesh;

	// EMP Machine Button Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMP Machine")
		class UStaticMeshComponent* EMPMachineButtonMesh;

	// Charge zone mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMP Machine")
		class UStaticMeshComponent* EMPChargeZoneMesh;

	// Box Collision for the EMP Machine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMP Machine")
		class UBoxComponent* EMPMachineCollision;


	// Hitbox for button on EMP Machine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMP Machine")
		class UBoxComponent* EMPMachineButtonCollision;

	// EMP Charge zone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMP Machine")
		class USphereComponent* EMPChargeZone;

	// On click function for
	UFUNCTION(BlueprintCallable, Category = "EMP Machine")
	void OnButtonClicked();

	//Sets visibility of the charge zone
	UFUNCTION(BlueprintCallable, Category = "EMP Machine")
	void SetChargeZoneVisibility(bool bVisible);

	UFUNCTION()
		void OnEMPChargeZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEMPChargeZoneEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	class UExtractionSubsystem* ExtractionSubsystem;
};
