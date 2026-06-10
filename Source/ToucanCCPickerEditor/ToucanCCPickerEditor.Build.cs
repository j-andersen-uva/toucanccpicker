using UnrealBuildTool;

public class ToucanCCPickerEditor : ModuleRules
{
    public ToucanCCPickerEditor(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "ControlRig",
                "RigVM"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",
                "Slate",
                "SlateCore",
                "EditorFramework",
                "LevelEditor",
                "InputCore",
                "Projects",
                "ControlRigEditor",
                "LevelSequence",
                "MovieScene",
                "MovieSceneTools"
            }
        );
    }
}
