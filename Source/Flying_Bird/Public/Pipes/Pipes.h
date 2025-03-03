// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Pipes.generated.h"

/*
 * This Class handles the attributes and operations of the pipes.
 */
UCLASS()
class FLYING_BIRD_API APipes : public AActor
{
	GENERATED_BODY()

	// Create a root
	UPROPERTY()
	USceneComponent* Root;

	// The mesh of the bottom pipe
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TubeBottomMesh;

	// The mesh of the top pipe
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TubeTopMesh;

	// The collision when the bird score the point
	UPROPERTY(EditAnywhere)
	UBoxComponent* HitPoint;

	// The time after which the pipes will be destroyed
	UPROPERTY(EditAnywhere)
	float DestroyDelay = 20.f;

	// The time the pipes have been alive
	float ElapsedTime = 0.f;

	// The speed of the pipes
	UPROPERTY(EditAnywhere)
	FVector DirectionSpeed = FVector(-500.f, 0, 0);

public:
	// Sets default values for this actor's properties
	APipes();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Get the hit point collision box
	UBoxComponent* GetHitPoint() const { return HitPoint; }

	// Get the top pipe mesh
	FORCEINLINE UStaticMeshComponent* GetTopPipeMesh() const { return TubeTopMesh; }

	// Get the bottom pipe mesh
	FORCEINLINE UStaticMeshComponent* GetBottomPipeMesh() const { return TubeBottomMesh; }
};
