// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdGameState.h"
#include "Kismet/GameplayStatics.h"

// Add score
void ABirdGameState::AddScore(const int Score)
{
	// Add the score
	CurrentScore += Score;

	// Broadcast the score
	OnScore.Broadcast(CurrentScore);
}

// On dead
void ABirdGameState::OnBirdDead()
{
	// Broadcast the dead event
	OnDead.Broadcast();
	
	// Reset the current score
	CurrentScore = 0; 
	
	// Check if the score is greater than the max score
	if (CurrentScore > MaxScore)
		MaxScore = CurrentScore;

	// Set the game over state
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
