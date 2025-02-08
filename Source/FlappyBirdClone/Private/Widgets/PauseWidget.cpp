// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/PauseWidget.h"
#include "Game/BirdGameState.h"
#include "Other/Getter.h"

// Called when the widget is constructed
void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Call the function to bind the buttons events
	BindButtons();
}

// The function to bind the buttons events
void UPauseWidget::BindButtons()
{
	// Bind the resume button
	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeButtonClicked);

	// Bind the quit button
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::OnQuitButtonClicked);
}

// The function to resume the game
// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseWidget::OnResumeButtonClicked()
{
	// Get the bird game state and check if it is valid
	const ABirdGameState* BirdGameState = UGetter::GetBirdGameState(GetWorld());
	if (!BirdGameState) return;

	// Get the bird controller and check if it is valid
	ABirdController* BirdController = UGetter::GetBirdController(GetWorld());
	if (!BirdController) return;

	// Broadcast the resume event
	BirdGameState->OnBirdPause(BirdController);
}

// The function to quit the game
// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseWidget::OnQuitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
