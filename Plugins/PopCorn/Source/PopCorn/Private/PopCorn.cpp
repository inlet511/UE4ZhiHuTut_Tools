// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PopCorn.h"
#include "PopCornStyle.h"
#include "PopCornCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "PopUI.h"
#include "LevelEditor.h"
#include "PropertyEditorModule.h"
#include "MyStructCustomization.h"

static const FName PopCornTabName("PopCorn");

#define LOCTEXT_NAMESPACE "FPopCornModule"

void FPopCornModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPopCornStyle::Initialize();
	FPopCornStyle::ReloadTextures();

	FPopCornCommands::Register();

	//注册自定义属性
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("MyStruct", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyStructCustomization::MakeInstance));


	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPopCornCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FPopCornModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPopCornModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPopCornModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PopCornTabName, FOnSpawnTab::CreateRaw(this, &FPopCornModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("PopCornTabName", "PopCorn"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPopCornModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FPopCornStyle::Shutdown();

	FPopCornCommands::Unregister();
}

void FPopCornModule::PluginButtonClicked()
{

	FGlobalTabmanager::Get()->InvokeTab(PopCornTabName);
}

void FPopCornModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FPopCornCommands::Get().PluginAction);
}

TSharedRef<class SDockTab> FPopCornModule::OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SPopUI)
			]
		];
}

void FPopCornModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FPopCornCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPopCornModule, PopCorn)