// Some copyright should be here...

using UnrealBuildTool;

public class BugShowcase : ModuleRules
{
	public BugShowcase(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"BugShowcase/Public"
				
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"BugShowcase/Private",
				
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
				"Projects",
				"InputCore",
				"UnrealEd",
                "CoreUObject",
				"LevelEditor",
                "EditorStyle",
				"Slate", "SlateCore",
				"PropertyEditor",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
