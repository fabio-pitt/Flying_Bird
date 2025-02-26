// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/GameWidget.h"
#include "Game/BirdGameState.h"
#include "Other/Getter.h"

// Called when the widget is constructed
void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// At the start, set the countdown text visible
	CountdownText->SetVisibility(ESlateVisibility::Visible);

	// Cast the bird game state and check if it is valid
	BirdGameState = UGetter::GetBirdGameState(GetWorld());
	if (BirdGameState)
	{
		// Bind the score event
		BirdGameState->OnScore.AddDynamic(this, &UGameWidget::OnScore);

		// Bind the high score event
		BirdGameState->OnHighScore.AddDynamic(this, &UGameWidget::OnHighScore);
	}

	// if the platform playing the game is Android, show the pause button and set the event click
#if PLATFORM_ANDROID
	PauseButton->SetVisibility(ESlateVisibility::Visible);
	PauseButton->OnClicked.AddDynamic(this, &UGameWidget::OnPauseButtonClicked);
#else
	PauseButton->SetVisibility(ESlateVisibility::Hidden);
#endif
	
	// Get the game instance
	if (const auto BirdInstance = UGetter::GetBirdInstance(GetWorld()))
	{
		// Reset the texts
		OnScore(BirdInstance->GetCurrentScore());
		OnHighScore(BirdInstance->GetHighScore());
	}
}

// Called every tick
void UGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Avoid the tick function if the countdown text is already hidden
	if (CountdownText->GetVisibility() == ESlateVisibility::Hidden) return;

	// Get the current countdown in GameState
	const float Countdown = BirdGameState->GetCountdown();
	if (Countdown > 0) // is counting
	{
		// Round up the countdown int
		const int8 CountdownInt = FMath::CeilToInt(Countdown);
		CountdownText->SetText(FText::AsNumber(CountdownInt));
	}
	else // is ended
	{
		CountdownText->SetVisibility(ESlateVisibility::Hidden);
	}
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
// ReSharper disable once CppMemberFunctionMayBeConst
void UGameWidget::OnPauseButtonClicked()
{
	// Get the player controller
	const auto PlayerController = UGetter::GetBirdController(GetWorld());
	if (!PlayerController) return;

	// Pause the game
	PlayerController->PauseGame();
}
