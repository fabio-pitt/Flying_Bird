// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/BirdInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Other/Logs.h"

// Initialize the game
void UBirdInstance::Init()
{
	Super::Init();
	ULogs::Info("New Instance");

	// Load the game
	Execute_LoadGame(this);

	// Create a new game if the save game is null
	if (!BirdSave) Execute_NewGame(this);

	// Save the game
	Execute_SaveGame(this);
}

// Create a new save game
void UBirdInstance::NewGame_Implementation()
{
	// Call the implementation of the interface
	ISaveLoadInterface::NewGame_Implementation();
	
	// Create the new save game object and set it as the current saved game
	if (USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UBirdSave::StaticClass()))
	{
		// Cast the save game to the BirdSave class
		BirdSave = Cast<UBirdSave>(NewSaveGame);
		if (!BirdSave) ULogs::Error("NewGame: cannot cast Bird Save");
		else ULogs::Info("NewGame: game created");
	}
	else ULogs::Error("NewGame: cannot create save game");
}

// Save the game
void UBirdInstance::SaveGame_Implementation()
{
	// Call the implementation of the interface
	ISaveLoadInterface::SaveGame_Implementation();
	
	// Check if the save game is valid and save it, log an error if not
	if (BirdSave) UGameplayStatics::SaveGameToSlot(BirdSave, SaveName, 0);
	else ULogs::Error("SaveGame: Bird Save is null");
}

// Load the game
void UBirdInstance::LoadGame_Implementation()
{
	// Call the implementation of the interface
	ISaveLoadInterface::LoadGame_Implementation();
	
	// Check if the save game exist and load it
	if (UGameplayStatics::DoesSaveGameExist(SaveName, 0))
	{
		BirdSave = Cast<UBirdSave>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));
		if (!BirdSave) ULogs::Error("LoadGame: cannot cast the game from slot");
		else ULogs::Info("LoadGame: game loaded");
	}

	// Print an error message if the save game is not found
	else ULogs::Warning("LoadGame: there is no save");
}

// Get the game
UBirdSave* UBirdInstance::GetGame_Implementation()
{
	// Call the implementation of the interface
	ISaveLoadInterface::GetGame_Implementation();
	
	// Check if the save game is valid and return it
	if (!BirdSave)
	{
		// Print an error message if the save game is null
		ULogs::Error("GetGame: Bird Save is null");
		return nullptr;
	}

	return BirdSave;
}

// Delete the game - not used
void UBirdInstance::DeleteSave_Implementation()
{
	// Call the implementation of the interface
	ISaveLoadInterface::DeleteSave_Implementation();
	
	// Check if the save game exist
	if (UGameplayStatics::DoesSaveGameExist(SaveName, 0))
	{
		// Delete the game object
		if (UGameplayStatics::DeleteGameInSlot(SaveName, 0))
		{
			// Delete the game reference
			BirdSave = nullptr;
		}
		else ULogs::Error("DeleteSave: cannot delete the game");
	}
	else ULogs::Error("DeleteSave: there is no save");
}

/********** SETTER **********/

// Set the high score
void UBirdInstance::SetHighScore(const uint32 Score) const
{
	if (BirdSave) BirdSave->SetHighScore(Score);
}

// Set the mute state
void UBirdInstance::SetAudioState(const bool IsEnabled) const
{
	if (BirdSave) BirdSave->SetAudioState(IsEnabled);
}

/********** GETTER **********/

// Get the high score
uint32 UBirdInstance::GetHighScore() const
{
	if (!BirdSave) return 0;
	return BirdSave->GetHighScore();
}

// Get the mute state
bool UBirdInstance::GetAudioState() const
{
	if (!BirdSave) return false;
	return BirdSave->GetAudioState();
}
