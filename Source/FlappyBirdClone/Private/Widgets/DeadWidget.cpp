// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/DeadWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Other/Getter.h"

// Called when the widget is constructed
void UDeadWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the restart button
	if (RestartButton) RestartButton->OnClicked.AddDynamic(this, &UDeadWidget::OnRestartButtonClicked);

	// Bind the quit button
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UDeadWidget::OnQuitButtonClicked);
}

// The function to set the texts
void UDeadWidget::SetTexts() const
{
	// Get the game instance
	const auto BirdInstance = UGetter::GetBirdInstance(GetWorld());
	if (!BirdInstance) return;

	// Set the texts
	if (ReachedScoreText) ReachedScoreText->SetText(FText::AsNumber(BirdInstance->GetCurrentScore()));
	if (HighScoreText) HighScoreText->SetText(FText::AsNumber(BirdInstance->GetHighScore()));
}

// Called when the restart button is clicked
// ReSharper disable once CppMemberFunctionMayBeConst
void UDeadWidget::OnRestartButtonClicked()
{
	// Get the game instance
	const auto BirdInstance = UGetter::GetBirdInstance(GetWorld());
	if (!BirdInstance) return;

	// Reset the score
	BirdInstance->SetCurrentScore(0);
	if (ReachedScoreText) ReachedScoreText->SetText(FText::AsNumber(0));

	// Restart the level
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

// Called when the quit button is clicked
// ReSharper disable once CppMemberFunctionMayBeConst
void UDeadWidget::OnQuitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
