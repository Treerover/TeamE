// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

#include "QuestBase.generated.h"


UENUM()
enum class EQuestType : uint8
{
	TEMP = 0 UMETA(DisplayName = "TEMP"),
};

UENUM()
enum class EObjectiveType : uint8
{
	Location = 0 UMETA(DisplayName = "Location"),
	Picture = 1 UMETA(DisplayName = "Picture"),
};

USTRUCT(BlueprintType)
struct FObjectiveDetails
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ObjectiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectiveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOptional;
};

USTRUCT(BlueprintType)
struct FStageDetails
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjectiveDetails> Objetives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MoneyReward;


};

USTRUCT(BlueprintType)
struct FQuestDetails : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LogDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TrackingtDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStageDetails> Stage;

};


UCLASS()
class TEAMECAPSTONE_API AQuestBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Variable")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Variable")
	FQuestDetails QuestDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Variable")
	int CurrentStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Variable")
	FStageDetails CurrentStageDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Variable")
	TMap<FString, int> CurrentObjectiveDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Variable")
	bool IsComplete;


};
