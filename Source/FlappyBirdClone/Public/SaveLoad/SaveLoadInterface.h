// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "BirdSave.h"
#include "UObject/Interface.h"
#include "SaveLoadInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USaveLoadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This is the Interface that manages the game data
 */
class FLAPPYBIRDCLONE_API ISaveLoadInterface
{
	GENERATED_BODY()

public:
	// Create a new game
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SaveLoad")
	void NewGame();
	
	// Save the game
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SaveLoad")
	void SaveGame();

	// Load the game
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SaveLoad")
	void LoadGame();

	// Get the game
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SaveLoad")
	UBirdSave* GetGame();
	
	// Delete the game - not implemented
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SaveLoad")
	void DeleteSave();
};
