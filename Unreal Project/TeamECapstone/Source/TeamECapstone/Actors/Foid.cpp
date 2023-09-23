// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foid.h"
#include "Actors/FishSwarm.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFoid::AFoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera Mesh"));
    SetRootComponent(Mesh);
    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
    UStaticMesh* Asset = MeshAsset.Object;
    Mesh->SetStaticMesh(Asset);
    Mesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
    Mesh->SetCollisionProfileName("NoCollision");
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AFoid::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AFoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector location = GetActorLocation();

    TurnSpeed = MySwarm->TurnSpeed;
    Speed = MySwarm->Speed;
    // use motivations to update direction
    Alignment = FVector(0, 0, 0);
    Coherence = FVector(0, 0, 0);
    Avoidance = FVector(0, 0, 0);
    NeighborCount = 0;
    for(AFoid* b : MySwarm->Swarm)
    {
        if (b)
        {
            if (b == this)
            {
                continue;
            }
            if ((GetActorLocation() - b->GetActorLocation()).Length() > NeighborRadius)
            {
                continue;
            }
            if (FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), b->GetActorLocation() - GetActorLocation()))) > FOV)
            {
                continue;
            }
            NeighborCount++;
            Alignment += b->GetActorForwardVector();
            Coherence += b->GetActorLocation();
            if (((GetActorLocation(), b->GetActorLocation()).Length()) < AvoidDistance)
            {
                Avoidance += GetActorLocation() - b->GetActorLocation();
            }
        }
    }

    if (NeighborCount == 0)
    {
        // give up and go home;
        Direction = (MySwarm->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    }
    /*else
    {
        Alignment = Alignment.GetSafeNormal();
        Avoidance = Avoidance.GetSafeNormal();
        Coherence = Coherence / NeighborCount;
        Coherence -= GetActorLocation();
        Coherence = Coherence.GetSafeNormal();

        FRandomStream RandomStream(FMath::Rand());

        FVector ran = RandomStream.VRand() * FMath::RandRange(0.0f, 1.0f);
        FVector SwarmDir = MySwarm->Target->GetActorLocation() - GetActorLocation();
        Direction = (SwarmDir * 0.2f + ran + Avoidance * 1.5f + Coherence + 0.36f * Alignment).GetSafeNormal();

    }*/



    // turn towards direction
    FRotator facing = UKismetMathLibrary::MakeRotFromX(Direction);
    FRotator newRot = FMath::RInterpTo(GetActorRotation(), facing, DeltaTime, TurnSpeed);
    SetActorRotation(newRot);

    // move forward
    FVector newPos = GetActorLocation() + Direction * Speed * DeltaTime;
    SetActorLocation(newPos);
}

void AFoid::SetSwarm(AFishSwarm* swarm)
{
    MySwarm = swarm;
    Speed = swarm->Speed;
    TurnSpeed = swarm->TurnSpeed;
    NeighborRadius = swarm->NeighborRadius;
    FOV = swarm->FOV;
    AvoidDistance = swarm->AvoidDistance;
}
