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
	AudioMuteButton->OnClicked.AddDynamic(this, &UAudioMute::ToggleAudioMute);

	// Call the function to set the volume
	SetVolume();

	// Change the button image
	ChangeButtonStyle();
}

// Toggle the audio mute
// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void UAudioMute::ToggleAudioMute()
{
	// Check the validation of the game instance, the audio mute button and the master sound class
	if (!BirdInstance || !AudioMuteButton || !MasterSoundClass) return;
	
	// Change the audio state
	BirdInstance->SetAudioState(!BirdInstance->GetAudioState());

	// Call the function to set the volume
	SetVolume();

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
	NormalBrush.TintColor = NormalColor;
	ButtonStyle.SetNormal(NormalBrush);

	// Set the button for the hovered state
	FSlateBrush HoveredBrush;
	HoveredBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);
	HoveredBrush.TintColor = HoveredColor;
	ButtonStyle.SetHovered(HoveredBrush);

	// Set the button for the un-hovered state
	FSlateBrush UnhoveredBrush;
	UnhoveredBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);
	UnhoveredBrush.TintColor = NormalColor;
	ButtonStyle.SetHovered(UnhoveredBrush);

	// Set the button for the pressed state
	FSlateBrush PressedBrush;
	PressedBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);
	PressedBrush.TintColor = PressedColor;
	ButtonStyle.SetPressed(PressedBrush);

	// Apply the button style
	AudioMuteButton->SetStyle(ButtonStyle);
}

// Set the volume
void UAudioMute::SetVolume() const
{
	// Set the volume of the master sound class
	if (BirdInstance && MasterSoundClass)
		MasterSoundClass->Properties.Volume = BirdInstance->GetAudioState() ? 1 : 0;
}