#include "EventTest.h"
#include "STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "SEventTest"

void SEventTest::Construct(const FArguments& InArgs)
{
	//_OnStartTest����SEventTest�ڹ���ʱ����ĺ���ָ��
	OnTestDelegate = InArgs._OnStartTest;
	ChildSlot
		[
			SNew(SVerticalBox)
			//-----------------------------//
			+ SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(60.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("TextDefaultValue0", "SnapCamera :"))
					]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(150.0f)
					[
						SAssignNew(TestButtonPtr, SButton)
						//��ť�����ʱ��ִ��OnTestButtonClicked
						.OnClicked(this, &SEventTest::OnTestButtonClicked)
						.Text(LOCTEXT("Login", "SnapCameraButton"))
					]
				]
			]
			//-----------------------------//
			+ SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(150.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("TextDefaultValue1", "SecondTestLine"))
					]
				]
			]
		];
}

FReply SEventTest::OnTestButtonClicked()
{
	//FString usn = TestTextOnePtr->GetText().ToString();
	//FString pwd = TestTextTwoPtr->GetText().ToString();

	//ִ���ڹ���ʱ����ĺ���ָ��
	OnTestDelegate.ExecuteIfBound(TEXT("aa"), TEXT("bb"));
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE