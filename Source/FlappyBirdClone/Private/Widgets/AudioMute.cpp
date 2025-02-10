// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/AudioMute.h"
#include "Other/Getter.h"
#include "Sound/SoundClass.h"

// Native construct
void UAudioMute::NativeConstruct()
{
	Super::NativeConstruct();

	// Cache the game instance
	BirdInstance = UGetter::GetBirdInstance(GetWorld());

	// When the mute button is clicked, call the function to toggle the audio mute
	if (AudioMuteButton) AudioMuteButton->OnClicked.AddDynamic(this, &UAudioMute::ToggleAudioMute);
		
	// Change the button style
	ChangeButtonStyle();

	// Set the volume of the master sound class
	if (MasterSoundClass) MasterSoundClass->Properties.Volume = BirdInstance->GetAudioState() ? 1 : 0;
}

// Toggle the audio mute
void UAudioMute::ToggleAudioMute()
{
	// Check the validation of the game instance, the audio mute button and the master sound class
	if (!BirdInstance || !AudioMuteButton || !MasterSoundClass) return;
	
	// Change the audio state
	BirdInstance->SetAudioState(!BirdInstance->GetAudioState());
	
	// Set the volume of the master sound class
	MasterSoundClass->Properties.Volume = BirdInstance->GetAudioState() ? 1 : 0;

	// Change the button image
	ChangeButtonStyle();
}

// Change the button image
void UAudioMute::ChangeButtonStyle() const
{
	// Check the validation of the game instance and the button
	if (!BirdInstance || !AudioMuteButton) return;

	// Check if the images are valid
	if (!AudioUnMutedImage || !AudioMutedImage) return;
	
	// Get the button style
	FButtonStyle ButtonStyle = AudioMuteButton->GetStyle();

	// Set the button for the normal state
	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);
	NormalBrush.TintColor = FLinearColor(0, 0, 0, 1);

	// Set the button for the hovered state
	FSlateBrush HoveredBrush;
	HoveredBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);
	HoveredBrush.TintColor = FLinearColor(0.35, 0.35, 0.35, 1);

	// Set the button for the pressed state
	FSlateBrush PressedBrush;
	PressedBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);
	PressedBrush.TintColor = FLinearColor(0.3, 0.15, 0.15, 1);

	// Update the button states
	ButtonStyle.SetNormal(NormalBrush);
	ButtonStyle.SetHovered(HoveredBrush);
	ButtonStyle.SetPressed(PressedBrush);

	// Apply the button style
	AudioMuteButton->SetStyle(ButtonStyle);
}
