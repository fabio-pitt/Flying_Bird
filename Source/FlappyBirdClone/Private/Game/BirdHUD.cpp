// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/BirdHUD.h"
#include "Other/Getter.h"
#include "Other/Logs.h"

// Called when the game starts
void ABirdHUD::BeginPlay()
{
	Super::BeginPlay();

	// Call the function to create the widgets
	CreateWidgets();

	// Call the function to set the widgets visibility
	DefaultWidgetsVisibility();

	// Check if the game state is valid and bind the events
	BindEvents();

	// Unpause
	OnPause(false);
}


// The function to create the widgets
void ABirdHUD::CreateWidgets()
{
	CreateGameWidget();
	CreatePauseWidget();
	CreateDeadWidget();
}

// The function to create the game widget
void ABirdHUD::CreateGameWidget()
{
	// Check if the game widget class is valid
	if (GameWidgetClass)
	{
		// Create the game widget
		GameWidget = Cast<UGameWidget>(GameWidgetClass);

		// If the game widget is valid, add it to the viewport, else print an error
		if (GameWidget) GameWidget->AddToViewport();
		else ULogs::Warning("Cannot create the game widget");
	}
	// If the game widget class is not set or valid, log a warning
	else ULogs::Warning("The game widget class is not set");
}

// The function to create the pause widget
void ABirdHUD::CreatePauseWidget()
{
	// Check if the pause widget class is valid
	if (PauseWidgetClass)
	{
		// Create the pause widget
		PauseWidget = Cast<UPauseWidget>(PauseWidgetClass);

		// If the pause widget is valid, add it to the viewport, else print an error
		if (PauseWidget) PauseWidget->AddToViewport();
		else ULogs::Warning("Cannot create the pause widget");
	}
	// If the pause widget class is not set or valid, log a warning
	else ULogs::Warning("The pause widget class is not set");
}

// The function to create the dead widget
void ABirdHUD::CreateDeadWidget()
{
	// Check if the dead widget class is valid
	if (DeadWidgetClass)
	{
		// Create the dead widget
		DeadWidget = Cast<UDeadWidget>(DeadWidgetClass);

		// If the dead widget is valid, add it to the viewport, else print an error
		if (DeadWidget) DeadWidget->AddToViewport();
		else ULogs::Warning("Cannot create the dead widget");
	}
	// If the dead widget class is not set or valid, log an error
	else ULogs::Warning("The dead widget class is not set");
}

// The function to begin the visibility
void ABirdHUD::DefaultWidgetsVisibility() const
{
	if (GameWidget) GameWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	if (PauseWidget) PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	if (DeadWidget) DeadWidget->SetVisibility(ESlateVisibility::Hidden);
}


// The function to bind the events
void ABirdHUD::BindEvents()
{
	// Get the bird game state and check if it is valid
	ABirdGameState* BirdGameState = UGetter::GetBirdGameState(GetWorld());
	if (!BirdGameState) return;
	
	// Bind the score event
	BirdGameState->OnScore.AddDynamic(this, &ABirdHUD::OnScore);

	// Bind the high score event
	BirdGameState->OnHighScore.AddDynamic(this, &ABirdHUD::OnScore);

	// Bind the pause event
	BirdGameState->OnPause.AddDynamic(this, &ABirdHUD::OnPause);

	// Bind the dead event
	BirdGameState->OnDead.AddDynamic(this, &ABirdHUD::OnDead);
}


// The function to update the score
// ReSharper disable once CppMemberFunctionMayBeConst
void ABirdHUD::OnScore(const uint32 CurrentScore)
{
	if (GameWidget) GameWidget->OnScore(CurrentScore);
}

// The function to update the pause
// ReSharper disable once CppMemberFunctionMayBeConst
void ABirdHUD::OnPause(const bool IsPaused)
{
	// Check if the pause widget is valid
	if (!PauseWidget) { ULogs::Warning("Controller - OnPause: Pause widget not found"); return; }

	// Check the player controller
	ABirdController* PlayerController = UGetter::GetBirdController(GetWorld());
	if (!PlayerController) return;
	
	// If the game is paused
	if (IsPaused)
	{
		// Set the pause widget as visible
		PauseWidget->SetVisibility(ESlateVisibility::Visible);

		// Call the function in the player controller to show the mouse cursor and set the input mode "UI only"
		PlayerController->ShowCursor_SetWidgetFocus(PauseWidget);
	}

	// If the game is unpaused
	else
	{
		// Set the pause widget as hidden (not visible and not hittable)
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);

		// Call the function in the player controller to hide the mouse cursor and set the input mode "Game only"
		PlayerController->HideCursor_SetGameFocus();
	}
}

// The function to update the dead
// ReSharper disable once CppMemberFunctionMayBeConst
void ABirdHUD::OnDead()
{
	// Check if the dead widget is valid
	if (!DeadWidget) { ULogs::Warning("Controller - OnDead: Dead widget not found"); return; }

	// Set the dead widget texts and show it
	DeadWidget->SetTexts();
	DeadWidget->SetVisibility(ESlateVisibility::Visible);

	// Show the mouse cursor and set the input mode "UI only"
	if (ABirdController* BirdController = UGetter::GetBirdController(GetWorld()))
	{
		BirdController->SetShowMouseCursor(true);
		BirdController->SetInputMode(FInputModeUIOnly());
	}

	// Check if the game widget is valid
	if (!GameWidget) { ULogs::Warning("Controller - OnDead: Game widget not found"); return; }

	// Set the game widget visibility
	GameWidget->SetVisibility(ESlateVisibility::Hidden);
}
