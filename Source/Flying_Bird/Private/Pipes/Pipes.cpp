// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Pipes/Pipes.h"
#include "Flying_Bird/Flying_Bird.h"

// Sets default values
APipes::APipes()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the root component
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	// Create the pipe on bottom
	TubeBottomMesh = CreateDefaultSubobject<UStaticMeshComponent>("TubeBottom");
	TubeBottomMesh->SetupAttachment(GetRootComponent());

	// Create the pipe on top
	TubeTopMesh = CreateDefaultSubobject<UStaticMeshComponent>("TubeTop");
	TubeTopMesh->SetupAttachment(GetRootComponent());

	// Create the hit point collision box
	HitPoint = CreateDefaultSubobject<UBoxComponent>("HitPoint");
	HitPoint->SetupAttachment(GetRootComponent());

	// Set the collision types
	TubeBottomMesh->SetCollisionObjectType(PIPE);
	TubeTopMesh->SetCollisionObjectType(PIPE);
	HitPoint->SetCollisionObjectType(SCORE);
}

// Called every frame
void APipes::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Check if the pipe is destructible
	if (DestroyDelay <= 0) return;

	// Updated the timer
	ElapsedTime += DeltaSeconds;

	// Move the pipes
	if (ElapsedTime < DestroyDelay)
	{
		// Calculate the direction and get the new location
		const FVector NewLocation = GetActorLocation() + DirectionSpeed * DeltaSeconds;

		// Set the new location
		SetActorLocation(NewLocation);
	}

	// Destroy the pipes
	else Destroy();
}
