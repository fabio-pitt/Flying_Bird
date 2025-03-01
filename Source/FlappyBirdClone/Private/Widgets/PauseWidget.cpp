// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/PauseWidget.h"
#include "Game/BirdGameState.h"
#include "Other/Getter.h"

// Called when the widget is constructed
void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get the score text
	GetScore();

	// Call the function to bind the buttons events
	BindButtons();
}

// The function to bind the buttons events
void UPauseWidget::BindButtons()
{
	// Bind the resume button
	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeButtonClicked);

	// Bind the quit button
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::OnQuitButtonClicked);
}

// The function to load the game
void UPauseWidget::GetScore() const
{	
	// Get the game instance
	const auto BirdInstance = UGetter::GetBirdInstance(GetWorld());
	if (!BirdInstance) return;

	// Get the current score and set as text
	if (CurrentScoreText) CurrentScoreText->SetText(FText::AsNumber(BirdInstance->GetCurrentScore()));

	// Get the high score and set as text
	if (HighScoreText) HighScoreText->SetText(FText::AsNumber(BirdInstance->GetHighScore()));
}

// The function to resume the game
// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseWidget::OnResumeButtonClicked()
{
	// Get the bird game state, checking if it's valid and call the pause
	if (const ABirdGameState* BirdGameState = UGetter::GetBirdGameState(GetWorld()))
		BirdGameState->OnBirdPause();
}

// The function to quit the game
// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseWidget::OnQuitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
