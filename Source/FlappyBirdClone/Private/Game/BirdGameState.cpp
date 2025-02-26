// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/BirdGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Other/Getter.h"
#include "Other/Logs.h"

// Constructor
ABirdGameState::ABirdGameState():
	BirdInstance(nullptr), ScoreSound(nullptr), DeadSound(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game start
void ABirdGameState::BeginPlay()
{
	Super::BeginPlay();

	// Get the game instance
	BirdInstance = UGetter::GetBirdInstance(GetWorld());

	// Countdown is the start countdown
	Countdown = StartCountdown;
}

// Called every tick
void ABirdGameState::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(-1, .001, FColor::Red, "BirdGameState::Tick");

	// Countdown to start the game
	Countdown -= DeltaSeconds;
	if (Countdown <= 0) // When the countdown reach zero
	{
		OnStartGame.Broadcast(); // Start game event
		SetActorTickEnabled(false); // Disable the tick
	}
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
		
	// Unpause the game
	OnPause.Broadcast(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

// Unpause
void ABirdGameState::UnpauseGame(APlayerController* Controller) const
{
	// Log a message
	ULogs::Info("Game unpaused");
		
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