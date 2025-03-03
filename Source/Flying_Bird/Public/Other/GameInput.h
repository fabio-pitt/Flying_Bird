// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "GameInput.generated.h"

/**
 * In this Class there are input actions that the player can do.
 */
UCLASS()
class FLYING_BIRD_API UGameInput : public UDataAsset
{
	GENERATED_BODY()

public:
	// Input to move the bird
	UPROPERTY(EditAnywhere)
	UInputAction* Fly;

	// Input to pause the game
	UPROPERTY(EditAnywhere)
	UInputAction* Pause;
};
