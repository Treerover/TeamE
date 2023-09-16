// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TeamECapstone : ModuleRules
{
	public TeamECapstone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateIncludePaths.AddRange(new string[] {
			"TeamECapstone/Actors",
			"TeamECapstone/Components",
			"TeamECapstone/Enums",
			"TeamECapstone/Gamemodes",
			"TeamECapstone/Managers",
			"TeamECapstone/Controllers",
			"TeamECapstone/Actors/Abilities",
			"TeamECapstone/Actors/Pawns",
			"TeamECapstone/Actors/Weapons",
			"TeamECapstone"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
