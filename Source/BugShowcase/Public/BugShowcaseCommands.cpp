// Some copyright should be here...

#include "BugShowcasePrivatePCH.h"
#include "BugShowcaseCommands.h"

#define LOCTEXT_NAMESPACE "FBugShowcaseModule"

void FBugShowcaseCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "BugShowcase", "Bring up BugShowcase window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
