// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class  NearAuthUEPluginServerTarget : TargetRules //Change this line according to the name of your project
{
    public  NearAuthUEPluginServerTarget(TargetInfo Target) : base(Target) //Change this line according to the name of your project
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        Type = TargetType.Server;
        bUsesSteam = true;

        ExtraModuleNames.Add("NearAuthUEPlugin");
    }
}