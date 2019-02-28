#include "MyStructCustomization.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "DetailLayoutBuilder.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "MyStructCustomization"

TSharedRef<IPropertyTypeCustomization> FMyStructCustomization::MakeInstance()
{
	return MakeShareable(new FMyStructCustomization());
}

void FMyStructCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//uint32 NumChildren;
	//StructPropertyHandle->GetNumChildren(NumChildren);

	//for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	//{
	//	const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();

	//	if (ChildHandle->GetProperty()->GetName() == TEXT("SomeUProperty"))
	//	{
	//		SomeUPropertyHandle = ChildHandle;
	//	}
	//}

	//check(SomeUPropertyHandle.IsValid());


	//HeaderRow
	//	.NameContent()
	//	[
	//		StructPropertyHandle->CreatePropertyNameWidget(LOCTEXT("Name","New property header name"), LOCTEXT("Name", "New property Tooltip"))
	//	]
	//	.ValueContent()
	//	.MinDesiredWidth(500)
	//	[
	//		SNew(STextBlock)
	//		.Text(LOCTEXT("Extra info", "Some new representation"))
	//		.Font(IDetailLayoutBuilder::GetDetailFont())
	//	];
}

void FMyStructCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

}

#undef LOCTEXT_NAMESPACE