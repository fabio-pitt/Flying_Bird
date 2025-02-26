// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/GameWidget.h"
#include "Widgets/PauseWidget.h"
#include "Widgets/DeadWidget.h"
#include "BirdHUD.generated.h"

/*
 * This Class manage the game HUD.
 */
UCLASS()
class FLAPPYBIRDCLONE_API ABirdHUD : public AHUD
{
	GENERATED_BODY()

	// The main widget class
	UPROPERTY(EditDefaultsOnly)
	UUserWidget* GameWidgetClass;

	// The main widget
	UPROPERTY()
	UGameWidget* GameWidget;

	// The pause widget class
	UPROPERTY(EditDefaultsOnly)
	UUserWidget* PauseWidgetClass;

	// The pause widget
	UPROPERTY()
	UPauseWidget* PauseWidget;

	// The dead widget class
	UPROPERTY(EditDefaultsOnly)
	UUserWidget* DeadWidgetClass;

	// The dead widget
	UPROPERTY()
	UDeadWidget* DeadWidget;

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called to create the widgets
	void CreateWidgets();

	// Called to create the game main ui widget
	void CreateGameWidget();

	// Called to create the pause ui widget
	void CreatePauseWidget();

	// Called to create the dead ui widget
	void CreateDeadWidget();

	// Called to set the widgets visibility
	void DefaultWidgetsVisibility() const;

	// Called to bind the events
	void BindEvents();

public:
	// Called when the score is updated
	UFUNCTION()
	void OnScore(uint32 CurrentScore);

	// Called when the game is paused
	UFUNCTION()
	void OnPause(const bool IsPaused);

	// Called when the bird is dead
	UFUNCTION()
	void OnDead();
};
