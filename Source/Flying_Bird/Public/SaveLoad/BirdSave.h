// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BirdSave.generated.h"

/**
 * This is the SaveGame Object that persists high score and audio settings between game sessions.
 */
UCLASS()
class FLYING_BIRD_API UBirdSave : public USaveGame
{
	GENERATED_BODY()

protected:
	// The high score of the game
	UPROPERTY(SaveGame)
	uint32 HighScore = 0;

	// The audio state
	UPROPERTY(SaveGame)
	bool AudioEnabled = true;

public:
	/** SCORE **/
	// Set the high score value
    void SetHighScore(const uint32 HiScore) { HighScore = HiScore; }

	// Get the high score value
	uint32 GetHighScore() const { return HighScore; }

	/** AUDIO **/
	// Set the audio state
	void SetAudioState(const bool IsEnabled) { AudioEnabled = IsEnabled; }

	// Get the audio state
	bool GetAudioState() const { return AudioEnabled; }
};
