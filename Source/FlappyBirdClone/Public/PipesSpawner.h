// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pipes.h"
#include "GameFramework/Actor.h"
#include "PipesSpawner.generated.h"

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

	// The timer to spawn the pipes
	float SpawnTimer = 0.f;

	// The range to spawn the pipes
	UPROPERTY(EditAnywhere)
	FFloatRange SpawnRange = FFloatRange(-500, 500);

public:
	// Sets default values for this actor's properties
	APipesSpawner();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The function to spawn the pipes
	void SpawnPipes() const;
};
