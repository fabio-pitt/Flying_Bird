// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Other/Getter.h"

// The function to construct the widget
void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Load the game info
	GetHighScore();

	// Bind the start button
	if (StartButton) StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartButtonClicked);

	// Bind the quit button
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitButtonClicked);
}

// The function to load the game
void UMenuWidget::GetHighScore() const
{	
	// Get the game instance
	const auto BirdInstance = UGetter::GetBirdInstance(GetWorld());
	if (!BirdInstance) return;

	// Get the high score and set as text
	if (HighScoreText) HighScoreText->SetText(FText::AsNumber(BirdInstance->GetHighScore()));
}

// The function to start the game on button clicked
// ReSharper disable once CppMemberFunctionMayBeConst
void UMenuWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

// The function to quit the game on button clicked
// ReSharper disable once CppMemberFunctionMayBeConst
void UMenuWidget::OnQuitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
