// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PandaTools.h"
#include "PandaToolsStyle.h"
#include "PandaToolsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "WidgetDemo.h"
#include "RoadTool.h"
#include "FoliageFarmer.h"
#include "PropertyEditorModule.h"

static const FName PandaToolsTabName("PandaTools");

#define LOCTEXT_NAMESPACE "FPandaToolsModule"

void FPandaToolsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPandaToolsStyle::Initialize();
	FPandaToolsStyle::ReloadTextures();

	FPandaToolsCommands::Register();
	
	//新建了一个命令列表
	PluginCommands = MakeShareable(new FUICommandList);

	//在新建的命令列表中进行了关联，让 OpenPluginWindow 命令被 PluginButtonClicked 函数处理
	PluginCommands->MapAction(
		FPandaToolsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPandaToolsModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

		//向菜单中加入项，命令列表为PluginCommands，并指明使用 AddMenuExtension 处理它
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPandaToolsModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

		//向工具栏中加入项，命令列表为PluginCommands，并指明使用 AddToolbarExtension 处理它
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPandaToolsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	// 向全局Tab管理器注册一个名称为 PandaToolsTabName 的Tab，并指明它在生成的时候使用 OnSpawnPluginTab 函数进行初始化(真正的绘制)
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PandaToolsTabName, FOnSpawnTab::CreateRaw(this, &FPandaToolsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPandaToolsTabTitle", "PandaTools"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

// 使用传入的Builder去真正地增加一个菜单入口
// 使用OpenPluginWindow命令去响应该入口
void FPandaToolsModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FPandaToolsCommands::Get().OpenPluginWindow);
}

// 使用传入的Builder去真正地增加一个工具栏按钮
// 使用OpenPluginWindow命令去响应该按钮
void FPandaToolsModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FPandaToolsCommands::Get().OpenPluginWindow);
}

void FPandaToolsModule::ShutdownModule()
{
	FPandaToolsStyle::Shutdown();

	FPandaToolsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PandaToolsTabName);
}

TSharedRef<SDockTab> FPandaToolsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//注册自定义Details面板内容
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("MyClass", FOnGetDetailCustomizationInstance::CreateStatic(&FMyCustomization::MakeInstance));

	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPandaToolsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PandaTools.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SFoliageFarmer)
			]
		];
}

// PluginButtonClicked 函数的作用是打开Tab
// 借助全局Tab管理器
// 如果已经打开面板，则聚焦，如果未打开面板，则新创建
void FPandaToolsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(PandaToolsTabName);
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPandaToolsModule, PandaTools)