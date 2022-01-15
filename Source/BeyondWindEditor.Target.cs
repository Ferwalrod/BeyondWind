// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BeyondWindEditorTarget : TargetRules
{
	public BeyondWindEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] { "BeyondWind", "Automatinator", "BeyondWindEditor" });
		//ExtraModuleNames.AddRange( new string[] { "BeyondWind" } );
		//ExtraModuleNames.Add("BeyondWind");
		//ExtraModuleNames.Add("BeyondWindEditor");
		//ExtraModuleNames.Add("Automatinator");
	}
}
