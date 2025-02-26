// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Game/BirdInstance.h"
#include "AudioMute.generated.h"

/**
 * This is the Widget Class relative to the audio button,
 * handles the images and the colors for state change with relative functions
 * and the sound class with the relative function for the audio state
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

	// The master sound class
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundClass* MasterSoundClass;

public:
	// The image used when the audio is not muted
	UPROPERTY(EditAnywhere, Category="Button State")
	UTexture2D* AudioUnMutedImage;

	// The image used when the audio is muted
	UPROPERTY(EditAnywhere, Category="Button State")
	UTexture2D* AudioMutedImage;

	// The color of the button used for the normal state
	UPROPERTY(EditAnywhere, Category="Button State")
	FLinearColor NormalColor = FLinearColor(0, 0, 0, 1);

	// The color of the button used for the hovered state
	UPROPERTY(EditAnywhere, Category="Button State")
	FLinearColor HoveredColor = FLinearColor(0.35, 0.35, 0.35, 1);

	// The color of the button used for the pressed state
	UPROPERTY(EditAnywhere, Category="Button State")
	FLinearColor PressedColor = FLinearColor(0.3, 0.15, 0.15, 1);

protected:
	// The function to construct the widget
	virtual void NativeConstruct() override;

	// Function to toggle the audio mute
	UFUNCTION(BlueprintCallable)
	void ToggleAudioMute();

	// Change the button image
	void ChangeButtonStyle() const;
};
