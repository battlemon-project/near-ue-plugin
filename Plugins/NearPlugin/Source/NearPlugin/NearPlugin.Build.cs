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

			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "libprotobuf.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "address_sorting.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "gpr.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "grpc.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "grpc++.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "upb.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_synchronization.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_graphcycles_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_base.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_civil_time.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_debugging_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_demangle_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_int128.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_log_severity.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_malloc_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_raw_logging_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_spinlock_wait.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_stacktrace.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_strings.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_strings_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_symbolize.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_throw_delegate.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_time.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_time_zone.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_city.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_bad_optional_access.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_bad_variant_access.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "cares.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_cord.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_cord_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_cordz_functions.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_cordz_handle.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_cordz_info.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "crypto.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_exponential_biased.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_hash.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_hashtablez_sampler.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_low_level_hash.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_distributions.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_platform.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_pool_urbg.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_randen.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_randen_hwaes.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_randen_hwaes_impl.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_randen_slow.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_internal_seed_material.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_seed_gen_exception.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_random_seed_sequences.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_raw_hash_set.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "re2.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "ssl.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_status.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_statusor.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "absl_str_format_internal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "zlibstatic.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathCpp, "crypt32.lib"));
			Console.WriteLine("... near_lib.dll -> " + Path.Combine("$(TargetOutputDir)/near_lib.dll", ThirdPartyPath, "/bin/near_lib.dll"));

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
