// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Bird.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Widget.h"
#include "Other/GameInput.h"
#include "BirdController.generated.h"

/*
 * This Class manages player input and character control interactions.
 */
UCLASS()
class FLAPPYBIRDCLONE_API ABirdController : public APlayerController
{
	GENERATED_BODY()

public:
	// Input mapping
	UPROPERTY(EditAnywhere)
	UInputMappingContext* IMC;

	// The input actions
	UPROPERTY(EditAnywhere)
	UGameInput* Input;

	// The enhanced input component
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	// The bird to control
	UPROPERTY()
	ABird* Bird;
	
	// Sets default values for this actor's properties
	ABirdController();

protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	// Called to check the input component
	bool CheckInputComponents();
	
	// Called to bind the input actions
	void BindInputActions();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to move the bird
	void MoveBird();
	
public:
	// Called to pause the game - on desktop platforms
#if PLATFORM_WINDOWS
	void PauseGame();
#endif

	// Show the cursor and set the focus on the widget
	void ShowCursor_SetWidgetFocus(UWidget* WidgetToFocus);

	// Hide the cursor and set the focus on game
	void HideCursor_SetGameFocus();
};
