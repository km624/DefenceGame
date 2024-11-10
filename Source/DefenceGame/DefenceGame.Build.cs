// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DefenceGame : ModuleRules
{
	public DefenceGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "DefenceGame" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" ,
            "HeadMountedDisplay"});
    }
}
