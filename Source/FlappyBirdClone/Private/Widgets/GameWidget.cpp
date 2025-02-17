// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/GameWidget.h"
#include "Game/BirdGameState.h"
#include "Other/Getter.h"

// Called when the widget is constructed
void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Cast the bird game state and check if it is valid
	ABirdGameState* BirdGameState = UGetter::GetBirdGameState(GetWorld());
	if (!BirdGameState) return;
	
	// Bind the score event
	BirdGameState->OnScore.AddDynamic(this, &UGameWidget::OnScore);

	// Bind the high score event
	BirdGameState->OnHighScore.AddDynamic(this, &UGameWidget::OnHighScore);

	if (PauseButton)
	{
		// Bind the pause button if the player is using an Android device
#if PLATFORM_ANDROID // this code is executed only in Android
		PauseButton->SetVisibility(ESlateVisibility::Visible);
		PauseButton->OnClicked.AddDynamic(this, &UGameWidget::OnPauseButtonClicked);
#else
		PauseButton->SetVisibility(ESlateVisibility::Hidden);
#endif
	}
	
	// Get the game instance
	const auto BirdInstance = UGetter::GetBirdInstance(GetWorld());
	if (!BirdInstance) return;

	// Reset the texts
	OnScore(BirdInstance->GetCurrentScore());
	OnHighScore(BirdInstance->GetHighScore());
}

// On score
// ReSharper disable once CppMemberFunctionMayBeConst
void UGameWidget::OnScore(const uint32 CurrentScore)
{
	if (ScoreText) ScoreText->SetText(FText::AsNumber(CurrentScore));
}

// On max score
// ReSharper disable once CppMemberFunctionMayBeConst
void UGameWidget::OnHighScore(const uint32 HighScore)
{
	if (HighScoreText) HighScoreText->SetText(FText::AsNumber(HighScore));
}

// On pause button clicked
void UGameWidget::OnPauseButtonClicked()
{
	// Get the player controller
	const auto PlayerController = UGetter::GetBirdController(GetWorld());
	if (!PlayerController) return;

	// Pause the game
	PlayerController->PauseGame();
}
