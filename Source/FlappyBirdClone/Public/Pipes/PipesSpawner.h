// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Pipes.h"
#include "GameFramework/Actor.h"
#include "PipesSpawner.generated.h"

/*
 * This Class manages the pipes spawn
 */
UCLASS()
class FLAPPYBIRDCLONE_API APipesSpawner : public AActor
{
	GENERATED_BODY()

	// The pipes to spawn
	UPROPERTY(EditAnywhere)
	TSubclassOf<APipes> Pipes;

	// The delay to spawn the pipes
	UPROPERTY(EditAnywhere)
	float SpawnDelay = 2.f;

	// The delay to spawn the pipes
	float Delay = 0.f;

	// The range to spawn the pipes
	UPROPERTY(EditAnywhere)
	FFloatRange SpawnRange = FFloatRange(-500, 500);

	// Check to start the game
	bool IsStarted = false;

public:
	// Sets default values for this actor's properties
	APipesSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to start the spawn
	UFUNCTION()
	void StartSpawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The function to spawn the pipes
	void SpawnPipes() const;
};
