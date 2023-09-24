// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DiveCage.h"
#include "Components/BoxComponent.h"
#include "TeamECapstoneCharacter.h"

// Sets default values
ADiveCage::ADiveCage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	CollisionBox = CreateDefaultSubobject <UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(Mesh);
	CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	TriggerBox = CreateDefaultSubobject <UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(Mesh);
	TriggerBox->SetCollisionProfileName("OverlapAllDynamic");
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADiveCage::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADiveCage::OnOverlapEnd);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->TargetArmLength = -700.0f;
	SpringArm->AddLocalRotation(FRotator(30, 0, 0));
	SpringArm->bDoCollisionTest = false;
	

	Tags.Add("DiveCage");
}

// Called when the game starts or when spawned
void ADiveCage::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetActorLocation();
}

void ADiveCage::LowerCage()
{

	SetActorLocation(GetActorLocation() + FVector(0, 0, -3));
	if (Player)
		Player->SetActorLocation(Player->GetActorLocation() + FVector(0, 0, -3));
}

void ADiveCage::RaiseCage()
{
	if (GetActorLocation().Z < OriginalLocation.Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0, 0, 3));
		if (Player)
			Player->SetActorLocation(Player->GetActorLocation() + FVector(0, 0, 3));
	}
}

void ADiveCage::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATeamECapstoneCharacter* p = Cast<ATeamECapstoneCharacter>(OtherActor);
	if (p)
	{
		Player = p;
	}
}

void ADiveCage::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player == OtherActor)
	{
		Player = nullptr;
	}
}

// Called every frame
void ADiveCage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

