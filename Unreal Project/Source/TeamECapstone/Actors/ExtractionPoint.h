// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionPoint.generated.h"

UCLASS()
class TEAMECAPSTONE_API AExtractionPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extraction Point")
		class UBoxComponent* ExtractionHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extraction Point")
		class UStaticMeshComponent* ExtractionMesh;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndexType, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsActive = false;

};
