/* Copyright 2009-2017 IKinema, Ltd. All Rights Reserved.
*
* IKinema API Library; SDK distribution
*
* This file is part of IKinema RunTime project http://www.ikinema.com
*
* Your use and or redistribution of this software in source and / or binary form, with or without
* modification, is subject to:
* (i) your ongoing acceptance of and compliance with the terms and conditions of
* the IKinema License Agreement; and
*
* (ii) your inclusion of this notice in any version of this software that you use
* or redistribute.
*
*
* A copy of the IKinema License Agreement is available by contacting
* IKinema Ltd., http://www.ikinema.com, support@ikinema.com
*
*/

using UnrealBuildTool;

public class IKinemaEditor : ModuleRules
{
	public IKinemaEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        //we are going to be building without PCH's
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //ensure IWYU is enforeced for potentially improved compile times
        bEnforceIWYU = false;

        PrivateIncludePaths.AddRange(new string[] {
			"IKinemaEditor/Public",
			"IKinemaEditor/Private",
			"IKinemaCore/Classes"
		});

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			AddEngineThirdPartyPrivateStaticDependencies(Target, "IKinema");
		}

		PublicDependencyModuleNames.AddRange(new string[] {"Projects", "Core", "CoreUObject", "Engine", "UnrealEd", "IKinemaCore", "JsonUtils", "BlueprintGraph", "AnimGraph", "Slate", 
				"SlateCore" ,
				"InputCore",
				"EditorStyle" });
		PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "Slate", "MessageLog", "JsonUtils", "ContentBrowser","AssetRegistry", "ClassViewer", "IKinemaRigTool"});
		PrivateIncludePathModuleNames.AddRange(new string[] { "AssetTools", "PropertyEditor", "JsonUtils" });
		DynamicallyLoadedModuleNames.AddRange(new string[] { "AssetTools", "PropertyEditor" });

	}
}