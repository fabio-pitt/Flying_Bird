// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameWidget.generated.h"

/**
 * 
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

public:
	// Called when the widget is constructed
	virtual void NativeConstruct() override;

	// Called when the score is updated
	UFUNCTION()
	void OnScore(uint32 CurrentScore);

	// Called when the high score is updated
	UFUNCTION()
	void OnHighScore(uint32 HighScore);
};
