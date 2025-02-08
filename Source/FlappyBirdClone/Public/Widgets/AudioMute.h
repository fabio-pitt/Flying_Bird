// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "AudioMute.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API UAudioMute : public UUserWidget
{
	GENERATED_BODY()

	// The button to mute the audio
	UPROPERTY(meta = (BindWidget))
	UButton* AudioMuteButton;

	// Check if the audio is muted
	bool bIsMuted = false;

	// The master sound class
	UPROPERTY(EditDefaultsOnly)
	USoundClass* MasterSoundClass;

	// The function to construct the widget
	virtual void NativeConstruct() override;

	// Function to toggle the audio mute
	UFUNCTION(BlueprintCallable)
	void ToggleAudioMute();
};
