// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DeadWidget.generated.h"

/**
 * This is the Widget Class that appears when the Bird character is dead.
 * It manages the reached score, the high score
 * and the buttons to restart or quit the game.
 */
UCLASS()
class FLAPPYBIRDCLONE_API UDeadWidget : public UUserWidget
{
	GENERATED_BODY()

	// The reached score text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ReachedScoreText;

	// The high score text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScoreText;

	// The button used to restart the game
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	// The button used to quit the game
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

public:
	// Called when the widget is constructed
	virtual void NativeConstruct() override;

	// Set scores texts
	void SetTexts() const;

protected:
	// Restart the game
	UFUNCTION()
	void OnRestartButtonClicked();

	// Quit the game
	UFUNCTION()
	void OnQuitButtonClicked();
};
