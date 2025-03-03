// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Other/Getter.h"
#include "Kismet/GameplayStatics.h"
#include "Other/Logs.h"

// The function to get the bird game state
ABirdGameState* UGetter::GetBirdGameState(const UWorld* Context)
{
	// Get the global game state
	AGameStateBase* GameState = UGameplayStatics::GetGameState(Context);
	if (!GameState)
	{
		ULogs::Error("GameState not found in world");
		return nullptr;
	}
	
	// Cast the bird game state
	ABirdGameState* BirdGameState = Cast<ABirdGameState>(GameState);
	if (!BirdGameState)
	{
		ULogs::Error("Cannot cast BirdGameState");
		return nullptr;
	}

	// Return the bird game state
	return BirdGameState;
}

// The function to get the bird
ABird* UGetter::GetBird(const UWorld* Context)
{
	// Get the bird in the world
	AActor* BirdActor = UGameplayStatics::GetActorOfClass(Context, ABird::StaticClass());
	if (!BirdActor)
	{
		ULogs::Error("Bird actor not found in world");
		return nullptr;
	}
	
	// Cast the bird
	ABird* Bird = Cast<ABird>(BirdActor);
	if (!Bird)
	{
		ULogs::Error("Cannot cast Bird actor");
		return nullptr;
	}

	// Return the bird
	return Bird;
}

// The function to get the player controller
ABirdController* UGetter::GetBirdController(const UWorld* Context)
{
	// Get the player controller in the world
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);
	if (!PlayerController)
	{
		ULogs::Error("PlayerController not found in world");
		return nullptr;
	}
	
	// Cast the player controller
	ABirdController* BirdController = Cast<ABirdController>(PlayerController);
	if (!BirdController)
	{
		ULogs::Error("Cannot cast BirdController");
		return nullptr;
	}

	// Return the bird
	return BirdController;
}

// The function to get the bird instance
UBirdInstance* UGetter::GetBirdInstance(const UWorld* Context)
{
	// Get the game instance in the world
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(Context);
	if (!GameInstance)
	{
		ULogs::Error("GameInstance not found in world");
		return nullptr;
	}
	
	// Cast the game instance
	UBirdInstance* BirdInstance = Cast<UBirdInstance>(GameInstance);
	if (!BirdInstance)
	{
		ULogs::Error("Cannot cast BirdInstance");
		return nullptr;
	}

	// Return the bird instance
	return BirdInstance;
}
