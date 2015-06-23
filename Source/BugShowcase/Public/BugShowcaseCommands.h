// Some copyright should be here...

#pragma once

#include "SlateBasics.h"
#include "BugShowcaseStyle.h"

class FBugShowcaseCommands : public TCommands<FBugShowcaseCommands>
{
public:

	FBugShowcaseCommands()
		: TCommands<FBugShowcaseCommands>(TEXT("BugShowcase"), NSLOCTEXT("Contexts", "BugShowcase", "BugShowcase Plugin"), NAME_None, FBugShowcaseStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};