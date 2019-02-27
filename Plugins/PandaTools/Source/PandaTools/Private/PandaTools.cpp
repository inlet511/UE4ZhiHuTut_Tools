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
	
	//�½���һ�������б�
	PluginCommands = MakeShareable(new FUICommandList);

	//���½��������б��н����˹������� OpenPluginWindow ��� PluginButtonClicked ��������
	PluginCommands->MapAction(
		FPandaToolsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPandaToolsModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

		//��˵��м���������б�ΪPluginCommands����ָ��ʹ�� AddMenuExtension ������
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPandaToolsModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

		//�򹤾����м���������б�ΪPluginCommands����ָ��ʹ�� AddToolbarExtension ������
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPandaToolsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	// ��ȫ��Tab������ע��һ������Ϊ PandaToolsTabName ��Tab����ָ���������ɵ�ʱ��ʹ�� OnSpawnPluginTab �������г�ʼ��(�����Ļ���)
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PandaToolsTabName, FOnSpawnTab::CreateRaw(this, &FPandaToolsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPandaToolsTabTitle", "PandaTools"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

// ʹ�ô����Builderȥ����������һ���˵����
// ʹ��OpenPluginWindow����ȥ��Ӧ�����
void FPandaToolsModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FPandaToolsCommands::Get().OpenPluginWindow);
}

// ʹ�ô����Builderȥ����������һ����������ť
// ʹ��OpenPluginWindow����ȥ��Ӧ�ð�ť
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
	//ע���Զ���Details�������
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

// PluginButtonClicked �����������Ǵ�Tab
// ����ȫ��Tab������
// ����Ѿ�����壬��۽������δ����壬���´���
void FPandaToolsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(PandaToolsTabName);
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPandaToolsModule, PandaTools)