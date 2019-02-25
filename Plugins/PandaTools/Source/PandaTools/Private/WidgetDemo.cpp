#include "WidgetDemo.h"
#include "EventTest.h"

#include "LevelEditorActions.h"
#include "Engine/Selection.h"

#define LOCTEXT_NAMESPACE "SWidgetdemo"

void SWidgetDemo::Construct(const FArguments& InArgs)
{
	ChildSlot
		.HAlign(HAlign_Left)
		[
			//构造SEventTest的时候，把函数指针传进其构造函数
			SNew(SEventTest).OnStartTest(this, &SWidgetDemo::OnMyTest)
		];
}

void SWidgetDemo::OnMyTest(FString usn, FString pwd)
{
	FLevelEditorActionCallbacks::SnapObjectToView_Clicked();
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		Actor->Modify();
		Actor->Destroy();
	}
}

#undef LOCTEXT_NAMESPACE