#pragma once
#include "SEditableTextBox.h"


DECLARE_DELEGATE_TwoParams(FTestDelegate, FString, FString);

class SEventTest : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SEventTest) {}
	SLATE_EVENT(FTestDelegate, OnStartTest)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	FReply OnTestButtonClicked();

	FTestDelegate OnTestDelegate;
	TSharedPtr<SEditableTextBox>TestTextOnePtr;
	TSharedPtr<SEditableTextBox>TestTextTwoPtr;
	TSharedPtr<SButton>TestButtonPtr;

};