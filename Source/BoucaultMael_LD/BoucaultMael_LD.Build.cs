// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BoucaultMael_LD : ModuleRules
{
	public BoucaultMael_LD(ReadOnlyTargetRules Target) : base(Target)
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
			"BoucaultMael_LD",
			"BoucaultMael_LD/Variant_Horror",
			"BoucaultMael_LD/Variant_Horror/UI",
			"BoucaultMael_LD/Variant_Shooter",
			"BoucaultMael_LD/Variant_Shooter/AI",
			"BoucaultMael_LD/Variant_Shooter/UI",
			"BoucaultMael_LD/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
