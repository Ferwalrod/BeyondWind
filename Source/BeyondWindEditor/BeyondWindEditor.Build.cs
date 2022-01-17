// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeyondWindEditor: ModuleRules
{
	public BeyondWindEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Slate", "SlateCore" });
		//PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UnrealEd", "HeadMountedDisplay" });
		//PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd", "XmlParser", "EditorStyle", "Slate", "SlateCore", "GraphEditor", "AppFramework", "PropertyEditor" });
		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
