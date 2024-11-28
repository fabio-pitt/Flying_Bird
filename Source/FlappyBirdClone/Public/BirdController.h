// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bird.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Controller.h"
#include "BirdController.generated.h"

UCLASS()
class FLAPPYBIRDCLONE_API ABirdController : public APlayerController
{
	GENERATED_BODY()

public:
	// Input mapping
	UPROPERTY(EditAnywhere)
	UInputMappingContext* IMC;
	
	// Input to move the bird
	UPROPERTY(EditAnywhere)
	UInputAction* InputMoveAction;

	// The bird to control
	UPROPERTY()
	ABird* Bird;
	
	// Sets default values for this actor's properties
	ABirdController();

protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The function to move the bird
	void MoveBird();
};
