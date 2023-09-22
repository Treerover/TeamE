// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MovmentStateTrigger.h"
#include "Components/BoxComponent.h"
#include "Pawns/TeamECapstoneCharacter.h"

// Sets default values
AMovmentStateTrigger::AMovmentStateTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject <UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionProfileName("OverlapAllDynamic");
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMovmentStateTrigger::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AMovmentStateTrigger::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AMovmentStateTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovmentStateTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovmentStateTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// On enter turn on water
	ATeamECapstoneCharacter* player = Cast<ATeamECapstoneCharacter>(OtherActor);

	if (player)
	{
		player->TrasitionMovementStates();
	}
}

void AMovmentStateTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//On exit turn off water
	ATeamECapstoneCharacter* player = Cast<ATeamECapstoneCharacter>(OtherActor);

	if (player)
	{
		player->TrasitionMovementStates();
	}
}

