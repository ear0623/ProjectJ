// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using UnrealBuildTool;

public class MySqlPluginLibrary : ModuleRules
{
	public MySqlPluginLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PublicSystemIncludePaths.Add("$(ModuleDir)/Public");
        

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "ExampleLibrary.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "lib64", "vs14", "libcrypto.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release","lib64", "vs14", "libssl.lib"));

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add("ExampleLibrary.dll");
			PublicDelayLoadDLLs.Add("libcrypto-3-x64.dll");
			PublicDelayLoadDLLs.Add("libssl-3-x64.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySqlPluginLibrary/Win64/ExampleLibrary.dll");
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySqlPluginLibrary/Win64/libcrypto-3-x64.dll");
            RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySqlPluginLibrary/Win64/libssl-3-x64.dll");
        }
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/MySqlPluginLibrary/Mac/Release/libExampleLibrary.dylib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string ExampleSoPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "MySqlPluginLibrary", "Linux", "x86_64-unknown-linux-gnu", "libExampleLibrary.so");
			PublicAdditionalLibraries.Add(ExampleSoPath);
			PublicDelayLoadDLLs.Add(ExampleSoPath);
			RuntimeDependencies.Add(ExampleSoPath);
		}
	}
}
