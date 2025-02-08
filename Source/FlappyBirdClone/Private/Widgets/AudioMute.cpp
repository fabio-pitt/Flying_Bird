// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Widgets/AudioMute.h"
#include "Sound/SoundClass.h"

// Native construct
void UAudioMute::NativeConstruct()
{
	Super::NativeConstruct();

	// When the mute button is clicked, call the function to toggle the audio mute
	if (AudioMuteButton) AudioMuteButton->OnClicked.AddDynamic(this, &UAudioMute::ToggleAudioMute);
}

// Toggle the audio mute
void UAudioMute::ToggleAudioMute()
{
	// Change the mute state
	bIsMuted = !bIsMuted;

	// Set the volume of the master sound class
	if (MasterSoundClass) MasterSoundClass->Properties.Volume = bIsMuted ? 0 : 1;
}
