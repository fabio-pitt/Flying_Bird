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
	if (AudioMuteButton)
	{
		// Bind the mute button
		AudioMuteButton->OnClicked.AddDynamic(this, &UAudioMute::ToggleAudioMute);

		// Change the button image
		ChangeButtonImage();

		// Change the image tint
		ChangeImageTint();
	}

	// Set the volume of the master sound class
	if (MasterSoundClass) MasterSoundClass->Properties.Volume = BirdInstance->GetAudioState() ? 1 : 0;
}

// Toggle the audio mute
void UAudioMute::ToggleAudioMute()
{
	// Check if the game instance is valid
	if (!BirdInstance) return;
	
	// Change the audio state
	BirdInstance->SetAudioState(!BirdInstance->GetAudioState());
	
	// Set the volume of the master sound class
	if (MasterSoundClass) MasterSoundClass->Properties.Volume = BirdInstance->GetAudioState() ? 1 : 0;

	// Change the button image
	ChangeButtonImage();
}

// Change the button image
void UAudioMute::ChangeButtonImage() const
{
	// Check if the game instance is valid
	if (!BirdInstance) return;
	
	// Get the button style
	FButtonStyle ButtonStyle = AudioMuteButton->GetStyle();

	// Set the button image
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(BirdInstance->GetAudioState() ? AudioUnMutedImage : AudioMutedImage);

	// Update all button states
	ButtonStyle.SetNormal(NewBrush);
	ButtonStyle.SetHovered(NewBrush);
	ButtonStyle.SetPressed(NewBrush);

	// Apply the button style
	AudioMuteButton->SetStyle(ButtonStyle);
}

// Change the image tint
void UAudioMute::ChangeImageTint() const
{
	// Get the button style
	FButtonStyle ButtonStyle = AudioMuteButton->GetStyle();

	// Set the button color for the normal state
	FSlateBrush NormalBrush;
	NormalBrush.TintColor = FLinearColor::Black;
	ButtonStyle.SetNormal(NormalBrush);

	// Set the button color for the hovered state
	FSlateBrush HoveredBrush;
	HoveredBrush.TintColor = FSlateColor(FLinearColor(0.35, 0.35, 0.35, 1));
	ButtonStyle.SetHovered(HoveredBrush);

	// Set the button color for the pressed state
	FSlateBrush PressedBrush;
	PressedBrush.TintColor = FSlateColor(FLinearColor(0.3, 0.15, 0.15, 1));;
	ButtonStyle.SetPressed(PressedBrush);
}