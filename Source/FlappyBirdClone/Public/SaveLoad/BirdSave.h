// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BirdSave.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API UBirdSave : public USaveGame
{
	GENERATED_BODY()

protected:
	// The high score of the game
	UPROPERTY(SaveGame)
	uint32 HighScore = 0;

public:
	// Set the high score value
	void SetHighScore(const uint32 HiScore) { HighScore = HiScore; }

	// Get the high score value
	uint32 GetHighScore() const { return HighScore; }
};
