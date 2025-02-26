// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/BirdGameState.h"
#include "GameWidget.generated.h"

/**
 * This is the Widget Class handling the game texts and buttons.
 * There are the initial countdown, the current score and the high score.
 * There is a button for the pause, visible only in Android platforms.
 */
UCLASS()
class FLAPPYBIRDCLONE_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

	// The text used to show the current score
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	// The text used to show the high score to beat
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScoreText;

	// The button used to open the pause menu on Android devices
	UPROPERTY(meta = (BindWidget))
	UButton* PauseButton;

	// The text to show the start countdown
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountdownText;

	// Cache the game state
	UPROPERTY()
	ABirdGameState* BirdGameState;

	// Called when the widget is constructed
	virtual void NativeConstruct() override;

	// Called every tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Called when the pause button is clicked - on Android devices
	UFUNCTION()
	void OnPauseButtonClicked();

public:
	// Called when the score is updated
	UFUNCTION()
	void OnScore(uint32 CurrentScore);

	// Called when the high score is updated
	UFUNCTION()
	void OnHighScore(uint32 HighScore);
};
