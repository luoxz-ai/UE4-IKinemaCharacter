using UnrealBuildTool;
using System;
using System.IO;
public class IKinemaCore : ModuleRules
{
	public IKinemaCore(ReadOnlyTargetRules Target) : base(Target)
	{

        //we are going to be building without PCH's
        //if we want to create an explicit PC for this module, would need to set "PrivatePCHHeaderFile"

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //ensure IWYU is enforeced for potentially improved compile times
        bEnforceIWYU = false;
        //bFasterWithoutUnity = true;


        //Currently only Win64 is supported
        // if ((Target.Platform == UnrealTargetPlatform.Win64))
        {
			PublicIncludePaths.AddRange(new string[]{
			"IKinemaCore/Classes",
			"IKinemaCore/Public",
			});
            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "AnimGraphRuntime", "HeadMountedDisplay", "SteamVR", "OpenVR"});
			PrivateDependencyModuleNames.Add("Projects");
        }
	}
}
