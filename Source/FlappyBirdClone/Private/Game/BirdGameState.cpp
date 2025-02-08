// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/BirdGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Other/Getter.h"
#include "Other/Logs.h"

// Constructor
ABirdGameState::ABirdGameState():
	BirdInstance(nullptr), ScoreSound(nullptr), DeadSound(nullptr)
{}

void ABirdGameState::BeginPlay()
{
	Super::BeginPlay();

	// Get the game instance
	BirdInstance = UGetter::GetBirdInstance(GetWorld());
}

// Score
void ABirdGameState::AddScore(const uint8 Score) const
{
	// Log a message
	ULogs::Info("Score");
	
	// Play sound
	UGameplayStatics::PlaySound2D(GetWorld(), ScoreSound, ScoreSoundVolume);
	
	// Add the score
	const uint32 NewScore = BirdInstance->GetCurrentScore() + Score;
	BirdInstance->SetCurrentScore(NewScore);

	// Check if the score is greater than the max score
	if (NewScore > BirdInstance->GetHighScore())
	{
		BirdInstance->SetHighScore(NewScore);
		OnHighScore.Broadcast(NewScore);
	}

	// Broadcast the score
	OnScore.Broadcast(NewScore);
}

// Pause
void ABirdGameState::OnBirdPause(APlayerController* Controller) const
{
	// Check if the controller is valid
	if (!Controller) { ULogs::Warning("BirdGameState - OnBirdPause: Controller not found?"); return; }
	
	// Check if the game is already paused: unpause
	if (UGameplayStatics::IsGamePaused(GetWorld()))
		UnpauseGame(Controller);

	// If the game is not paused: pause
	else PauseGame(Controller);
}

// Pause
void ABirdGameState::PauseGame(APlayerController* Controller) const
{
	// Log a message
	ULogs::Info("Game paused");

	// Show the mouse cursor and set the input mode "Game Only"
	Controller->SetShowMouseCursor(true);
	Controller->SetInputMode(FInputModeGameOnly());
		
	// Unpause the game
	OnPause.Broadcast(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

// Unpause
void ABirdGameState::UnpauseGame(APlayerController* Controller) const
{
	// Log a message
	ULogs::Info("Game unpaused");

	// Show the mouse cursor and set the input mode "Game Only"
	Controller->SetShowMouseCursor(false);
	Controller->SetInputMode(FInputModeGameOnly());
		
	// Unpause the game
	OnPause.Broadcast(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

// Dead
void ABirdGameState::OnBirdDead() const
{
	// Log a message
	ULogs::Info("Bird dead");

	// Play sound
	UGameplayStatics::PlaySound2D(GetWorld(), DeadSound, DeadSoundVolume);

	// Save the game
	ISaveLoadInterface::Execute_SaveGame(BirdInstance);
		
	// Broadcast the dead event
	OnDead.Broadcast();
	
	// Set the game over state
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}