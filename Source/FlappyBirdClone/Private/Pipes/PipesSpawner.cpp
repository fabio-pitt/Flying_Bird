// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Pipes/PipesSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APipesSpawner::APipesSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APipesSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Delay is set to the spawn delay
	Delay = SpawnDelay;
}

// Called every frame
void APipesSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the game is paused
	if (UGameplayStatics::IsGamePaused(GetWorld())) return;

	// Spawn the pipes following the delay
	Delay -= DeltaTime;
	if (Delay <= 0)
	{
		SpawnPipes();
		Delay = SpawnDelay;
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
