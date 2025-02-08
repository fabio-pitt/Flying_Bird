// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Logs.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API ULogs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Function to log an error message
	UFUNCTION()
	static void Error(const FString& Message);

	// Function to log a warning message
	UFUNCTION()
	static void Warning(const FString& Message);

	// Function to log an info message
	UFUNCTION()
	static void Info(const FString& Message);
};
