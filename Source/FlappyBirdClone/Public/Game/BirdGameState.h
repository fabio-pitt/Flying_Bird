// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "BirdInstance.h"
#include "GameFramework/GameStateBase.h"
#include "BirdGameState.generated.h"

// Declare delegates for score and dead events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScore, uint32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPause, bool, IsPaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API ABirdGameState : public AGameStateBase
{
	GENERATED_BODY()

	// The game instance cache
	UPROPERTY(Transient)
	UBirdInstance* BirdInstance;

	// The score point sound
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* ScoreSound;

	// The volume of the score point sound
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	float ScoreSoundVolume = 1.0f;

	// The dead sound
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* DeadSound;

	// The volume of the dead sound
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	float DeadSoundVolume = 1.0f;

public:
	// Delegate for score
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnScore OnScore;

	// Delegate for high score
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnScore OnHighScore;

	// Delegate for dead
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDead OnDead;

	// Delegate for pause
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPause OnPause;

	// Constructor to initialize values
	ABirdGameState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Add the current score
	void AddScore(uint8 Score = 1) const;
	
	// Called on pause
	void OnBirdPause(APlayerController* Controller) const;

	// Called when the game is paused
	void PauseGame(APlayerController* Controller) const;

	// Called when the game is unpaused
	void UnpauseGame(APlayerController* Controller) const;

	// Called on dead
	void OnBirdDead() const;
};
