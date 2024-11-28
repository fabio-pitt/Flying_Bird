// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BirdGameState.generated.h"

// Declare delegates for score and dead events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScore, int, CurrentScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API ABirdGameState : public AGameStateBase
{
	GENERATED_BODY()

	// The current score of the game
	UPROPERTY(VisibleAnywhere)
	int CurrentScore = 0;

	// The maximum score reached in the game
	int MaxScore = 0;

public:
	// Delegate for score
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnScore OnScore;

	// Delegate for dead
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDead OnDead;
	
	// Add the current score
	void AddScore(int Score = 1);

	// Called on dead
	void OnBirdDead();
};
