// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABirdController::ABirdController(): IMC(nullptr), InputMoveAction(nullptr), Bird(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Binds functionality to input
void ABirdController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check the input component
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent is null"));
		return;
	}

	// Cast the enhanced input component
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is null"));
		return;
	}

	// Move up
	EnhancedInputComponent->BindAction(InputMoveAction, ETriggerEvent::Started, this, &ABirdController::MoveBird);
}

void ABirdController::BeginPlay()
{
	Super::BeginPlay();
	
	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(IMC, 0);
	else UE_LOG(LogTemp, Error, TEXT("No Input Subsystem"));

	// Get the bird in the world
	AActor* BirdActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABird::StaticClass());
	if (!BirdActor)
	{
		UE_LOG(LogTemp, Error, TEXT("No bird found in world"));
		return;
	}

	// Cast the bird
	Bird = Cast<ABird>(BirdActor);
	if (!Bird)
	{
		UE_LOG(LogTemp, Error, TEXT("Bird cannot cast"));
		return; // redundant for now
	}
}

// The function to move the bird
// ReSharper disable once CppMemberFunctionMayBeConst
void ABirdController::MoveBird()
{
	if (Bird) Bird->ApplyImpulse();
}
                                                                         