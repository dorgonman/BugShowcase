// Some copyright should be here...

#include "BugShowcasePrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "BugShowcaseStyle.h"
#include "BugShowcaseCommands.h"

#include "LevelEditor.h"

#include "BaseClass.h"
#include "DerivedClass.h"

#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "Editor/PropertyEditor/Public/PropertyEditing.h"

#include "DerivedCustomization.h"

static const FName BugShowcaseTabName("BugShowcase");

#define LOCTEXT_NAMESPACE "FBugShowcaseModule"

void FBugShowcaseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBugShowcaseStyle::Initialize();
	FBugShowcaseStyle::ReloadTextures();

	FBugShowcaseCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBugShowcaseCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FBugShowcaseModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FBugShowcaseModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FBugShowcaseModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BugShowcaseTabName, FOnSpawnTab::CreateRaw(this, &FBugShowcaseModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FBugShowcaseTabTitle", "BugShowcase"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("DerivedClass", FOnGetDetailCustomizationInstance::CreateStatic(&FDerivedCustomization::MakeInstance));
}

void FBugShowcaseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	FBugShowcaseStyle::Shutdown();

	FBugShowcaseCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BugShowcaseTabName);
}

TSharedRef<SDockTab> FBugShowcaseModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs(
		/*bUpdateFromSelection=*/ false,
		/*bLockable=*/ false,
		/*bAllowSearch=*/ false,
		/*const ENameAreaSettings InNameAreaSettings =*/ FDetailsViewArgs::ENameAreaSettings::ObjectsUseNameArea,
		/*bHideSelectionTip=*/ true,
		/*InNotifyHook=*/ NULL,
		/*InSearchInitialKeyFocus=*/ false,
		/*InViewIdentifier=*/ NAME_None);

	TSharedPtr<IDetailsView> BaseClassView = EditModule.CreateDetailView(DetailsViewArgs);
	TSharedPtr<IDetailsView> DerivedClassView = EditModule.CreateDetailView(DetailsViewArgs);

	BaseClassView->SetObject(GetMutableDefault<UBaseClass>(), true);
	DerivedClassView->SetObject(GetMutableDefault<UDerivedClass>(), true);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.Padding(5)
			[
				BaseClassView.ToSharedRef()
			]
			+SHorizontalBox::Slot()
				.Padding(5)
			[
				DerivedClassView.ToSharedRef()
			]
		];
}

void FBugShowcaseModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(BugShowcaseTabName);
}

void FBugShowcaseModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FBugShowcaseCommands::Get().OpenPluginWindow);
}

void FBugShowcaseModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FBugShowcaseCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBugShowcaseModule, BugShowcase)