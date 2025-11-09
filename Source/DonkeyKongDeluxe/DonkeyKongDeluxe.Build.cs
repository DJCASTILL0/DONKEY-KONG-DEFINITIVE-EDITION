// RUTA: Source/DonkeyKongDeluxe/DonkeyKongDeluxe.Build.cs

using UnrealBuildTool;

public class DonkeyKongDeluxe : ModuleRules
{
    public DonkeyKongDeluxe(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG" // ¡ASEGÚRATE DE QUE "UMG" ESTÉ EN ESTA LISTA!
		});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}