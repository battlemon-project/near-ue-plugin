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
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../third_party/")); }
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
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
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
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;

			//string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

			string LibrariesPathCryptlib = Path.Combine(ThirdPartyPath, "lib", "win64", "Release", "cryptopp");
			//Console.WriteLine("... LibrariesPathCryptlib -> " + LibrariesPathCryptlib);

			string LibrariesPathCpp = Path.Combine(ThirdPartyPath, "lib", "win64", "Release", "NearCpp");
			//Console.WriteLine("... LibrariesPathCpp -> " + LibrariesPathCpp);
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "NearRPC.lib"));

#if UE_4_20_OR_LATER
RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.dll", ThirdPartyPath, "/bin/near_lib.dll"));
#else
			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/near_lib.dll", ThirdPartyPath, "/bin/near_lib.dll")));
#endif

		}

		if (isLibrarySupported)
		{


			string IncludePathCrypt = Path.Combine(ThirdPartyPath, "include", "cryptopp");
			//Console.WriteLine("... IncludePathCrypt -> " + IncludePathCrypt);
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath));
			string IncludePath = Path.Combine(ThirdPartyPath, "include");
			//Console.WriteLine("... IncludePath -> " + IncludePath);
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath));
			//cef
			//string str = Path.Combine(ThirdPartyPath, "include");
			//Console.WriteLine("... ThirdPartyPath -> " + str);
			//PublicIncludePaths.Add("J:/source/UE4/Test2/third_party/include");
			//PublicIncludePaths.Add(Path.Combine(ThirdPartyPath));
		}

		return true;
	}
}
