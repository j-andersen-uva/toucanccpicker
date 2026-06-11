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
                "ControlRigEditor",
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
                "LevelSequence",
                "LevelSequenceEditor",
                "MovieScene",
                "MovieSceneTools"
            }
        );
    }
}
