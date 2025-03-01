// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PauseWidget.generated.h"

/**
 * This is the Widget Class relative to the pause menu.
 * It handles the buttons for resume and quit.
 */
UCLASS()
class FLAPPYBIRDCLONE_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

	// The current score text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentScoreText;

	// The high score text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScoreText;

	// The resume button
	UPROPERTY(meta=(BindWidget))
	UButton* ResumeButton;

	// The quit button
	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton;

	// Called when the widget is constructed
	virtual void NativeConstruct() override;
	
	// Bind the buttons events
	void BindButtons();
	
	// Called when the resume button is clicked
	UFUNCTION()
	void OnResumeButtonClicked();

	// Called when the quit button is clicked
	UFUNCTION()
	void OnQuitButtonClicked();

public:
	// Function to load the game on start
	void GetScore() const;
};
