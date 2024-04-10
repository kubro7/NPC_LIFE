// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NPC_LIFE : ModuleRules
{
	public NPC_LIFE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput" 
		});
	}
}
