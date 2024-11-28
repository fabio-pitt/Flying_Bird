// Fill out your copyright notice in the Description page of Project Settings.

#include "PipesSpawner.h"

// Sets default values
APipesSpawner::APipesSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void APipesSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Spawn the pipes following the delay
	if (GetWorld()->GetRealTimeSeconds() - SpawnTimer > SpawnDelay)
	{
		SpawnPipes();
		SpawnTimer = GetWorld()->GetRealTimeSeconds();
	}
}

// Spawns the pipes
void APipesSpawner::SpawnPipes() const
{	
	// Get the min and max values from the range
	const float Min = SpawnRange.GetLowerBoundValue();
	const float Max = SpawnRange.GetUpperBoundValue();

	// Get X and Y value of this actor
	const float X = GetActorLocation().X;
	const float Y = GetActorLocation().Y;
	
	// Get the random spawn location
	const FVector SpawnLocation = FVector(X, Y, FMath::RandRange(Min, Max));
	const FRotator SpawnRotation = FRotator(0, 0, 0); // No rotation

	// Spawn the pipes
	GetWorld()->SpawnActor<APipes>(Pipes, SpawnLocation, SpawnRotation);
}
