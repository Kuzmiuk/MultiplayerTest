// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiKama : ModuleRules
{
    public MultiKama(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",

            "UMG",
            "Slate",
            "SlateCore",

            "OnlineSubsystem",
            "OnlineSubsystemSteam",
            "OnlineSubsystemUtils",

            "Niagara",

            "MultiplayerSessions"
        });
    }
}