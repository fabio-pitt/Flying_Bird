// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdClone/Public/MainWidget.h"
#include "BirdGameState.h"
#include "Kismet/GameplayStatics.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Set score text
	ScoreText->SetVisibility(ESlateVisibility::Visible);

	// Set dead text
	DeadText->SetVisibility(ESlateVisibility::Collapsed);

	// Get the game state
	AGameStateBase* MyGameState = UGameplayStatics::GetGameState(GetWorld());
	if (!MyGameState) return;

	// Cast the bird game state
	ABirdGameState* BirdGameState = Cast<ABirdGameState>(MyGameState);
	if (!BirdGameState) return;

	// Bind the score event
	BirdGameState->OnScore.AddDynamic(this, &UMainWidget::OnScore);

	// Bind the dead event
	BirdGameState->OnDead.AddDynamic(this, &UMainWidget::OnDead);
}

// On score
void UMainWidget::OnScore(const int CurrentScore)
{
	if (ScoreText) ScoreText->SetText(FText::AsNumber(CurrentScore));
}

// On dead
void UMainWidget::OnDead()
{
	if (DeadText) DeadText->SetVisibility(ESlateVisibility::Visible);
}
