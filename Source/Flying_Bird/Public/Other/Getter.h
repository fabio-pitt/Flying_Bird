// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Game/Bird.h"
#include "Game/BirdController.h"
#include "Game/BirdGameState.h"
#include "Game/BirdInstance.h"
#include "Getter.generated.h"

/**
 * This is a useful custom Library to get some game Classes.
 */
UCLASS()
class FLYING_BIRD_API UGetter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Function to get the bird game state
	UFUNCTION()
	static ABirdGameState* GetBirdGameState(const UWorld* Context);

	// Function to get the bird actor
	UFUNCTION()
	static ABird* GetBird(const UWorld* Context);

	// Function to get the player controller
	UFUNCTION()
	static ABirdController* GetBirdController(const UWorld* Context);

	// Function to get the game instance
	UFUNCTION()
	static UBirdInstance* GetBirdInstance(const UWorld* Context);
};
