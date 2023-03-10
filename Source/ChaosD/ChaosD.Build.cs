// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChaosD : ModuleRules
{
	public ChaosD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara","UMG" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

    }
}
