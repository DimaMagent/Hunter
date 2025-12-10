// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Hunter : ModuleRules
{
	public Hunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Hunter",
			"Hunter/Variant_Platforming",
			"Hunter/Variant_Platforming/Animation",
			"Hunter/Variant_Combat",
			"Hunter/Variant_Combat/AI",
			"Hunter/Variant_Combat/Animation",
			"Hunter/Variant_Combat/Gameplay",
			"Hunter/Variant_Combat/Interfaces",
			"Hunter/Variant_Combat/UI",
			"Hunter/Variant_SideScrolling",
			"Hunter/Variant_SideScrolling/AI",
			"Hunter/Variant_SideScrolling/Gameplay",
			"Hunter/Variant_SideScrolling/Interfaces",
			"Hunter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
