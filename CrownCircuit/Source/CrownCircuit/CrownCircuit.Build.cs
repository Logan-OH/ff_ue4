using UnrealBuildTool;

public class CrownCircuit : ModuleRules
{
    public CrownCircuit(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "Slate",
            "SlateCore",
            "HTTP",
            "Json",
            "JsonUtilities",
            "WebSockets"
        });
    }
}
