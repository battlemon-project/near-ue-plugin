// Copyright Epic Games, Inc. All Rights Reserved.
//using System;
using System.IO;
using UnrealBuildTool;

public class NearPlugin : ModuleRules
{
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../Content/third_party/")); }
	}

	public NearPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "WebSockets", "OpenSSL"
				// ... add other public dependencies that you statically link with here ...
			}
			);
		//PrivateDependencyModuleNames.AddRange("WebSockets");


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		LoadCEFLib(Target);
	}

	public bool LoadCEFLib(ReadOnlyTargetRules Target)
	{
		string LibrariesPath = Path.Combine(ThirdPartyPath, "lib");
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			//Console.WriteLine("... LibrariesPathCryptlib -> " + LibrariesPathCryptlib);

			string LibrariesPathPlatform = Path.Combine(LibrariesPath, ((Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32"));
			//Console.WriteLine("... LibrariesPathCpp -> " + LibrariesPathCpp);
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "NearRPC.lib"));

			AdditionalCodeGenDirectories.Add(Path.Combine(LibrariesPathPlatform, "NearRPC.lib"));

#if UE_4_20_OR_LATER

RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.dll", ThirdPartyPath + "bin\\near_lib.dll"));
#else

			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.dll", ThirdPartyPath + "bin\\near_lib.dll")));
#endif
		}
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Mac", "Release", "NearRPC.lib"));

#if UE_4_20_OR_LATER
RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.dll", ThirdPartyPath + "bin\\near_lib.dylib"));
#else

			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.dll", ThirdPartyPath + "bin\\near_lib.dylib")));
#endif
		}


		if ((Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.LinuxAArch64))
		{
			//Console.WriteLine("... LibrariesPathCryptlib -> " + LibrariesPathCryptlib);

			string LibrariesPathPlatform = Path.Combine(LibrariesPath, ((Target.Platform == UnrealTargetPlatform.LinuxAArch64) ? "LinuxAArch64" : "Linux"), "Release");
			//Console.WriteLine("... LibrariesPathCpp -> " + LibrariesPathCpp);
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "NearRPC.a"));

#if UE_4_20_OR_LATER
RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.so",  ThirdPartyPath + "bin\\near_lib.so"));
#else
			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.so", ThirdPartyPath + "bin\\near_lib.so")));
#endif
		}
		//Console.WriteLine("... ThirdPartyPath -> " + ThirdPartyPath);
		PrivateIncludePaths.Add(ThirdPartyPath);
		//PublicIncludePaths.Add(ThirdPartyPath);
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
		return true;
	}
}
