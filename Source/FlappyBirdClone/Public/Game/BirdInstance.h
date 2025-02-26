// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveLoad/SaveLoadInterface.h"
#include "BirdInstance.generated.h"

/**
 * This Class extend the Unreal GameInstance to be specialized in save game data.
 */
UCLASS()
class FLAPPYBIRDCLONE_API UBirdInstance : public UGameInstance, public ISaveLoadInterface
{
	GENERATED_BODY()

	// The current score
	uint32 CurrentScore = 0;

	// The current mute state
	bool bIsMuted = false;

	// The current saved game
	UPROPERTY(EditDefaultsOnly, Category="SaveLoad")
	UBirdSave* BirdSave = nullptr;

	// A name used to save the game
	UPROPERTY(EditDefaultsOnly, Category="SaveLoad")
	FString SaveName = "GameData";

	// Called when the game instance is initialized
	virtual void Init() override;

public:
	// The interface function to create a new game
	virtual void NewGame_Implementation() override;

	// The interface function to save the game
	virtual void SaveGame_Implementation() override;

	// The interface function to load the game
	virtual void LoadGame_Implementation() override;

	// The interface function to get the game
	virtual UBirdSave* GetGame_Implementation() override;

	// The interface function to delete the game - not implemented
	virtual void DeleteSave_Implementation() override;

	/********** SETTER **********/

	// Set the current score
	FORCEINLINE void SetCurrentScore(const uint32 Score) { CurrentScore = Score; }

	// Set the high score
	void SetHighScore(const uint32 Score) const;

	// Set the audio state
	void SetAudioState(const bool IsEnabled) const;

	/********** GETTER **********/

	// Get the current score
	FORCEINLINE uint32 GetCurrentScore() const { return CurrentScore; }

	// Get the high score
	uint32 GetHighScore() const;

	// Get the audio state
	bool GetAudioState() const;
};
