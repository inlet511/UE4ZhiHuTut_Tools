#include "PopUI.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "MyStruct.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IStructureDetailsView.h"

#define LOCTEXT_NAMESPACE "PopUI"

void SPopUI::Construct(const FArguments& InArgs)
{
	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//DetailsView����
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);

	//������һ���µ�Details���
	TSharedRef<IStructureDetailsView> ConfigPanel = PropertyModule.CreateStructureDetailView(DetailsViewArgs, FStructureDetailsViewArgs(),nullptr);
	
	structData = MakeShared<FStructOnScope>(FMyStruct::StaticStruct());

	//����Object
	ConfigPanel->SetStructureData(structData.ToSharedRef());

	TSharedPtr<SWidget> DetailsWidget = ConfigPanel->GetWidget();

	ChildSlot
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				SNew(SButton)
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				DetailsWidget.ToSharedRef()
			]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
				]
		];
}

#undef LOCTEXT_NAMESPACE