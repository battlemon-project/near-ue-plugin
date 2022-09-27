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
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			//Console.WriteLine("... LibrariesPathCryptlib -> " + LibrariesPathCryptlib);

			string LibrariesPathPlatform = Path.Combine(LibrariesPath, ((Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32"));
			//Console.WriteLine("... LibrariesPathCpp -> " + LibrariesPathCpp);
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "NearRPC.lib"));

			AdditionalCodeGenDirectories.Add(Path.Combine(LibrariesPathPlatform, "NearRPC.lib"));

#if UE_4_20_OR_LATER

RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/near_Rust.dll", ThirdPartyPath + "bin\\near_Rust.dll"));
#else

			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/near_Rust.dll", ThirdPartyPath + "bin\\near_Rust.dll")));
#endif
		}
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "MacOS", "libNearRPC.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "MacOS", "libresolv.9.tdb"));

#if UE_4_20_OR_LATER
RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.dylib", ThirdPartyPath + "bin\\libnear_Rust.dylib")); 
#else

			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.dylib", ThirdPartyPath + "bin\\libnear_Rust.dylib")));
#endif
		}


		if ((Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.LinuxAArch64))
		{
			//Console.WriteLine("... LibrariesPathCryptlib -> " + LibrariesPathCryptlib);

			string LibrariesPathPlatform = Path.Combine(LibrariesPath, ((Target.Platform == UnrealTargetPlatform.LinuxAArch64) ? "LinuxAArch64" : "Linux"));
			//PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "libNearRPC.so"));
			//PublicDelayLoadDLLs.Add("libNearRPC.so");
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "libNearRPC.a"));
			
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_cord.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_str_format_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_debugging_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_strerror.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_strings.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_strings_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_status.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_statusor.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_bad_optional_access.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_stacktrace.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_symbolize.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_int128.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_bad_variant_access.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_city.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_civil_time.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_cord_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_cordz_functions.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libaddress_sorting.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libcares.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libgpr.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libgrpc.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libgrpc++.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libprotobuf.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libupb.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_base.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_malloc_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_raw_logging_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_spinlock_wait.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_throw_delegate.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_time.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_time_zone.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_graphcycles_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_synchronization.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_cordz_handle.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_cordz_info.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_demangle_internal.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_exponential_biased.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_hash.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_hashtablez_sampler.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_log_severity.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_low_level_hash.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_distributions.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_seed_sequences.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_platform.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_seed_gen_exception.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_seed_material.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_randen_slow.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_randen_hwaes_impl.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_randen_hwaes.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_randen.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_random_internal_pool_urbg.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libre2.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "grpc/libabsl_raw_hash_set.a"));
			//PublicAdditionalLibraries.Add(Path.Combine(LibrariesPathPlatform, "libc.a"));
			
			//Console.WriteLine("... TargetOutputDir -> " + Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.so", ThirdPartyPath + "bin\\libnear_Rust.so"));
#if UE_4_20_OR_LATER
			RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.so",  ThirdPartyPath + "bin\\libnear_Rust.so"));
			//RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/libNearRPC.so",  LibrariesPathPlatform + "\\libNearRPC.so"));
#else
			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/third_party/bin/libnear_Rust.so", ThirdPartyPath + "bin\\libnear_Rust.so")));
			//RuntimeDependencies.Add(new RuntimeDependency(Path.Combine("$(TargetOutputDir)/libNearRPC.so",  LibrariesPathPlatform + "\\libNearRPC.so")));
#endif
		}

		
		PrivateIncludePaths.Add(Path.Combine(ThirdPartyPath));
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL"); 
		return true;
	}
}
