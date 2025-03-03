// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Flying_Bird : ModuleRules
{
	public Flying_Bird(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine",
			"InputCore", "EnhancedInput",
			"Slate", "SlateCore", "UMG"
		});
	}
}
