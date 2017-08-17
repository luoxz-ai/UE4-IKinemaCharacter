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

public class IKinemaRigTool : ModuleRules
{
    public IKinemaRigTool(ReadOnlyTargetRules Target) : base(Target)
    {

        //we are going to be building without PCH's
        //if we want to create an explicit PC for this module, would need to set "PrivatePCHHeaderFile"
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //ensure IWYU is enforeced for potentially improved compile times
        bEnforceIWYU = false;
       // bFasterWithoutUnity = true;


        PublicIncludePaths.Add("Editor/UnrealEd/Public");

        PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Projects",
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"RenderCore",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"PropertyEditor",
				"LevelEditor",
				"UnrealEd",
				"Kismet",
				"Persona",
				"ClassViewer",
				"AnimGraph",
				"AnimGraphRuntime",
				"IKinemaCore",
				"Persona",
				"PhysXVehicles",
				"JsonUtils",
				"Analytics"
			}
		);

		PublicAdditionalLibraries.Add("ws2_32.lib");
		PublicAdditionalLibraries.Add("Winhttp.lib");

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"MainFrame",
				"MeshUtilities",
			}
		);
    }
}
