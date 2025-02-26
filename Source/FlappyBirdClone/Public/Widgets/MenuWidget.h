// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MenuWidget.generated.h"

/**
 * This is the Widget Class relative to the main menu of the game.
 * It handles the buttons to start or quit the game
 * and the text corresponding to the saved highest score.
 */
UCLASS()
class FLAPPYBIRDCLONE_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	// The button to start the game
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	// The button to quit the game
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	// The high score text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScoreText;

	// The game level name
	UPROPERTY(EditDefaultsOnly)
	FName LevelName;
	
	// Native construct
	virtual void NativeConstruct() override;

	// Function to load the game on start
	void GetHighScore() const;

	// Called when the start button is clicked
	UFUNCTION()
	void OnStartButtonClicked();

	// Called when the quit button is clicked
	UFUNCTION()
	void OnQuitButtonClicked();
};
