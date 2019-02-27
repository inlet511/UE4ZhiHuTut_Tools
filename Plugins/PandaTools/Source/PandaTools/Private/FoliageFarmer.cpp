#include "FoliageFarmer.h"
#include "PropertyEditing.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Modules/ModuleManager.h"
#include "EdGraph/EdGraphSchema.h"


void SFoliageFarmer::Construct(const FArguments& InArgs)
{
    auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//DetailsView参数
    FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);

	//创建了一个新的Details面板
    ConfigPanel=PropertyModule.CreateDetailView(DetailsViewArgs); 

	//设置RootObjectCustomizationInstance
	//ConfigPanel->SetRootObjectCustomizationInstance(MakeShareable(new FRootObjectCustomization));

	//设置Object
    ConfigPanel->SetObject(UMyClass::StaticClass()->GetDefaultObject(true), true); 

	GraphObj = NewObject<UEdGraph>();
	GraphObj->Schema = UEdGraphSchema::StaticClass();
	GraphObj->AddToRoot();
	GraphEditorPtr = SNew(SGraphEditor).GraphToEdit(GraphObj);

    ChildSlot 
    [
        SNew(SVerticalBox)
        +SVerticalBox::Slot()
        .AutoHeight()
        [
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(300)
				.MinDesiredWidth(300)
				.MaxDesiredWidth(300)
				[
					SNew(SBorder)
					[
						ConfigPanel.ToSharedRef()
					]
				]
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				GraphEditorPtr->AsShared()
			]            
        ]
    ];
}

FReply UMyClass::TestClicked()
{
	float testValue = Cast<UMyClass>(UMyClass::StaticClass()->GetDefaultObject(true))->TestFloat;
	return FReply::Handled();
}


#define LOCTEXT_NAMESPACE "MyEditorModule"

TSharedRef<IDetailCustomization> FMyCustomization::MakeInstance()
{
	return MakeShareable(new FMyCustomization);
}

void FMyCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// This is where the core of the customization code will go.
	IDetailCategoryBuilder& Cat = DetailBuilder.EditCategory(TEXT("TestFloat"));


	//TWeakObjectPtr< AMyClass > MyObject = Cast< AMyClass >(Objects[0].Get());

	Cat.AddCustomRow(LOCTEXT("MyWarningRowFilterString", "Search Filter Keywords"))
		.WholeRowContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("MyWarningTest", "BaseString should not be empty!"))
		];
	//DetailBuilder.ForceRefreshDetails();
}

#undef LOCTEXT_NAMESPACE

