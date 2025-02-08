// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "BirdGameState.h"
#include "GameFramework/Actor.h"
#include "Bird.generated.h"

UCLASS()
class FLAPPYBIRDCLONE_API ABird : public AActor
{
	GENERATED_BODY()

public:
	// The mesh of the bird
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BirdMesh;

	// The force of the impulse to apply to the bird
	UPROPERTY(EditAnywhere)
	float ImpulseForce = 10.f;

	// The multiplier of the impulse to apply to the bird
	UPROPERTY(EditAnywhere)
	float ImpulseMultiplier = 10000.f;

	// The bird game state
	UPROPERTY(VisibleAnywhere)
	ABirdGameState* BirdGameState;

	// Sets default values for this actor's properties
	ABird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called to apply the impulse to the bird
	void ApplyImpulse() const;
};
