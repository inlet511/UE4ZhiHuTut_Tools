#include "PopUI.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "MyStruct.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "PopUI"

void SPopUI::Construct(const FArguments& InArgs)
{
	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//DetailsView参数
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);

	//创建了一个新的Details面板
	ConfigPanel = PropertyModule.CreateStructureDetailView(DetailsViewArgs);

	FMyStruct MyFirstStruct;

	//设置Object
	ConfigPanel->SetObject(MyFirstStruct);

	ChildSlot
		[
			SNew(SBorder)
			[
				ConfigPanel.ToSharedRef()
			]
		];
}

#undef LOCTEXT_NAMESPACE