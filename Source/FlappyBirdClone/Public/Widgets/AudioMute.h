// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Game/BirdInstance.h"
#include "AudioMute.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API UAudioMute : public UUserWidget
{
	GENERATED_BODY()

	// The game instance
	UPROPERTY()
	UBirdInstance* BirdInstance;

	// The button to mute the audio
	UPROPERTY(meta = (BindWidget))
	UButton* AudioMuteButton;

	// The image used when the audio is not muted
	UPROPERTY(EditDefaultsOnly, Category="Images")
	UTexture2D* AudioUnMutedImage;

	// The image used when the audio is muted
	UPROPERTY(EditDefaultsOnly, Category="Images")
	UTexture2D* AudioMutedImage;

	// The master sound class
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundClass* MasterSoundClass;

	// The function to construct the widget
	virtual void NativeConstruct() override;

	// Function to toggle the audio mute
	UFUNCTION(BlueprintCallable)
	void ToggleAudioMute();

	// Change the button image
	void ChangeButtonImage() const;

	// Change the image tint
	void ChangeImageTint() const;	
};
