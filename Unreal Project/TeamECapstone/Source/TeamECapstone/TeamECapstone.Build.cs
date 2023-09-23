// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TeamECapstone : ModuleRules
{
	public TeamECapstone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[] {
            "TeamECapstone/Actors",
            "TeamECapstone/Components",
            "TeamECapstone/Enums",
            "TeamECapstone/Gamemodes",
            "TeamECapstone/Managers",
            "TeamECapstone/Subsystems",
            "TeamECapstone/Controllers",
            "TeamECapstone/Actors/Abilities",
            "TeamECapstone/Actors/Pawns",
            "TeamECapstone/Actors/Weapons",
            "TeamECapstone/Actors/QuestSystem",
            "TeamECapstone",
        });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
