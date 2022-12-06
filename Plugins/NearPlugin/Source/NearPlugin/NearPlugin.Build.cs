// Copyright Epic Games, Inc. All Rights Reserved.
using System;
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
				"Core", "WebSockets", "HTTP", "Json"
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
		string LibrariesPath = Path.Combine(ThirdPartyPath, "lib");
		string extension = "";
		string LibrariesPathPlatform = "";

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			LibrariesPathPlatform = Path.Combine(LibrariesPath, ((Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32"));
			extension = "*.lib";

#if UE_4_20_OR_LATER

RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/near_Rust.dll", ThirdPartyPath + "bin\\near_Rust.dll"));
#else

			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/near_Rust.dll", ThirdPartyPath + "bin\\near_Rust.dll")));
#endif
		}
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			LibrariesPathPlatform = Path.Combine(LibrariesPath, "MacOS");
			extension = "*.a";
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "libresolv.9.tdb"));

#if UE_4_20_OR_LATER
RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.dylib", ThirdPartyPath + "bin\\libnear_Rust.dylib")); 
#else

			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.dylib", ThirdPartyPath + "bin\\libnear_Rust.dylib")));
#endif
		}


		if ((Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.LinuxAArch64))
		{
			LibrariesPathPlatform = Path.Combine(LibrariesPath, ((Target.Platform == UnrealTargetPlatform.LinuxAArch64) ? "LinuxAArch64" : "Linux"));
			extension = "*.a";
#if UE_4_20_OR_LATER
			RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.so",  ThirdPartyPath + "bin\\libnear_Rust.so"));
			//RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/libNearRPC.so",  LibrariesPathPlatform + "\\libNearRPC.so"));
#else
			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.so", ThirdPartyPath + "bin\\libnear_Rust.so")));
#endif
		}
		string[] LibrariesArray = Directory.GetFiles(LibrariesPathPlatform, extension, SearchOption.AllDirectories);
		Console.WriteLine(LibrariesPathPlatform);
		Console.WriteLine(extension);

		Console.WriteLine("Libraries_Dir_Begin----->");
		foreach (var value in LibrariesArray)
		{
			Console.WriteLine(value);
		}
		Console.WriteLine("----->Libraries_Dir_End");

		PublicAdditionalLibraries.AddRange(LibrariesArray);
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));

		PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
		PublicDefinitions.Add("GPR_FORBID_UNREACHABLE_CODE");
		PublicDefinitions.Add("GRPC_ALLOW_EXCEPTIONS=0");
		PublicDefinitions.Add("__NVCC__");

		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL"); 
		return true;
	}
}
