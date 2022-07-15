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
				"Core", "WebSockets"
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

			PublicAdditionalLibraries.Add("libprotobuf.a");
			PublicAdditionalLibraries.Add("libaddress_sorting.a");
			PublicAdditionalLibraries.Add("libgpr.a");
			PublicAdditionalLibraries.Add("libgrpc.a");
			PublicAdditionalLibraries.Add("libgrpc++.a");
			PublicAdditionalLibraries.Add("libupb.a");
			PublicAdditionalLibraries.Add("libabsl_synchronization.a");
			PublicAdditionalLibraries.Add("libabsl_graphcycles_internal.a");
			PublicAdditionalLibraries.Add("libabsl_base.a");
			PublicAdditionalLibraries.Add("libabsl_civil_time.a");
			PublicAdditionalLibraries.Add("libabsl_debugging_internal.a");
			PublicAdditionalLibraries.Add("libabsl_demangle_internal.a");
			PublicAdditionalLibraries.Add("libabsl_int128.a");
			PublicAdditionalLibraries.Add("libabsl_log_severity.a");
			PublicAdditionalLibraries.Add("libabsl_malloc_internal.a");
			PublicAdditionalLibraries.Add("libabsl_raw_logging_internal.a");
			PublicAdditionalLibraries.Add("libabsl_spinlock_wait.a");
			PublicAdditionalLibraries.Add("libabsl_stacktrace.a");
			PublicAdditionalLibraries.Add("libabsl_strings.a");
			PublicAdditionalLibraries.Add("libabsl_strings_internal.a");
			PublicAdditionalLibraries.Add("libabsl_symbolize.a");
			PublicAdditionalLibraries.Add("libabsl_throw_delegate.a");
			PublicAdditionalLibraries.Add("libabsl_time.a");
			PublicAdditionalLibraries.Add("libabsl_time_zone.a");
			PublicAdditionalLibraries.Add("libabsl_city.a");
			PublicAdditionalLibraries.Add("libabsl_bad_optional_access.a");
			PublicAdditionalLibraries.Add("libabsl_bad_variant_access.a");
			PublicAdditionalLibraries.Add("libcares.a");
			PublicAdditionalLibraries.Add("libabsl_cord.a");
			PublicAdditionalLibraries.Add("libabsl_cord_internal.a");
			PublicAdditionalLibraries.Add("libabsl_cordz_functions.a");
			PublicAdditionalLibraries.Add("libabsl_cordz_handle.a");
			PublicAdditionalLibraries.Add("libabsl_cordz_info.a");
			PublicAdditionalLibraries.Add("libcrypto.a");
			PublicAdditionalLibraries.Add("libabsl_exponential_biased.a");
			PublicAdditionalLibraries.Add("libabsl_hash.a");
			PublicAdditionalLibraries.Add("libabsl_hashtablez_sampler.a");
			PublicAdditionalLibraries.Add("libabsl_low_level_hash.a");
			PublicAdditionalLibraries.Add("libabsl_random_distributions.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_platform.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_pool_urbg.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_randen.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_randen_hwaes.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_randen_hwaes_impl.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_randen_slow.a");
			PublicAdditionalLibraries.Add("libabsl_random_internal_seed_material.a");
			PublicAdditionalLibraries.Add("libabsl_random_seed_gen_exception.a");
			PublicAdditionalLibraries.Add("libabsl_random_seed_sequences.a");
			PublicAdditionalLibraries.Add("libabsl_raw_hash_set.a");
			PublicAdditionalLibraries.Add("libre2.a");
			PublicAdditionalLibraries.Add("libssl.a");
			PublicAdditionalLibraries.Add("libabsl_status.a");
			PublicAdditionalLibraries.Add("libabsl_statusor.a");
			PublicAdditionalLibraries.Add("libabsl_str_format_internal.a");
			PublicAdditionalLibraries.Add("libzlibstatic.a");


			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Mac", "Release", "NearRPC.a"));

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

		
		PrivateIncludePaths.Add(Path.Combine(ThirdPartyPath));
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL"); 
		return true;
	}
}
