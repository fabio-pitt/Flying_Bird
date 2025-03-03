// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Other/Logs.h"

// The function to log an error
void ULogs::Error(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
	UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
}

// The function to log a warning
void ULogs::Warning(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

// The function to log an info
void ULogs::Info(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
}
