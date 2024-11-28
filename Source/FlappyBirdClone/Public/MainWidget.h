// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

	// The text used to show the score
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	// The text used when the bird is dead
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeadText;

	// Called when the widget is constructed
	virtual void NativeConstruct() override;

	// Called when the score is updated
	UFUNCTION()
	void OnScore(int CurrentScore);

	// Called when the bird is dead
	UFUNCTION()
	void OnDead();
};
