// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/BirdController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Other/Getter.h"
#include "Other/Logs.h"

// Sets default values
ABirdController::ABirdController():
	IMC(nullptr), Input(nullptr), EnhancedInputComponent(nullptr), Bird(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Binds functionality to input
void ABirdController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check the input component
	if (CheckInputComponent())
	{
		// Bind the input actions
		BindInputActions();
	}
}

// Checks the input component
bool ABirdController::CheckInputComponent()
{
	// Check the input component
	if (!InputComponent)
	{
		ULogs::Error("Controller - CheckInputComponent: No Input Component");
		return false;
	}
	
	// Cast and check the enhanced input component
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		ULogs::Error("Controller - CheckInputComponent: No Enhanced Input Component");
		return false;
	}
		
	return true;
}

// Binds the input actions
void ABirdController::BindInputActions()
{
	// Check the input
	if (!Input) { ULogs::Warning("Controller - BindInputActions: Input not found"); return; }
	
	// Jump
	if (!Input->Fly) ULogs::Warning("Controller - BindInputActions: Fly action not found");
	else EnhancedInputComponent->BindAction(Input->Fly, ETriggerEvent::Started, this, &ABirdController::MoveBird);

	// Pause
	if (!Input->Pause) ULogs::Warning("Controller - BindInputActions: Pause action not found");
	else EnhancedInputComponent->BindAction(Input->Pause, ETriggerEvent::Started, this, &ABirdController::PauseGame);
}

// Called when the game starts
void ABirdController::BeginPlay()
{
	Super::BeginPlay();

	// Set the resolution
	ConsoleCommand("r.setRes 720x1280");
	
	// Set the game focus
	HideCursor_SetGameFocus();
	
	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(IMC, 0);
	else ULogs::Error("Controller - BeginPlay: No Input Subsystem");

	// Get the bird in the world
	Bird = UGetter::GetBird(GetWorld());
}

// The function to move the bird
// ReSharper disable once CppMemberFunctionMayBeConst
void ABirdController::MoveBird()
{
	if (Bird) Bird->ApplyImpulse();
}

// The function to pause the game
// ReSharper disable once CppMemberFunctionMayBeConst
void ABirdController::PauseGame()
{
	if (const ABirdGameState* BirdGameState = UGetter::GetBirdGameState(GetWorld()))
		BirdGameState->OnBirdPause(this);
	else ULogs::Error("Controller - PauseGame: BirdGameState not found");
}

// Show the mouse cursor and set the input mode "UI only"
void ABirdController::ShowCursor_SetWidgetFocus(UWidget* WidgetToFocus)
{
	// Show the mouse cursor
	SetShowMouseCursor(true);

	// Set the input mode
	FInputModeUIOnly InputMode_UIOnly;
	InputMode_UIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode_UIOnly.SetWidgetToFocus(WidgetToFocus->TakeWidget());
	SetInputMode(InputMode_UIOnly);
}

// Hide the mouse cursor and set the input mode "Game only"
void ABirdController::HideCursor_SetGameFocus()
{
	// Hide the mouse cursor
	SetShowMouseCursor(false);

	// Set the input mode
	const FInputModeGameOnly InputMode_GameOnly;
	SetInputMode(InputMode_GameOnly);
}
