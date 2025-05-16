// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WhisperBag : ModuleRules
{
	public WhisperBag(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CinematicCamera" });
	}
}
