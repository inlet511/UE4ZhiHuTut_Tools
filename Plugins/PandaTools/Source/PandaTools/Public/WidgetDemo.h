#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

//DECLARE_DELEGATE_TwoParams(FTestDelegate, FString, FString);

class SWidgetDemo : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SWidgetDemo) {}
	//SLATE_EVENT(FTestDelegate, OnStartTest)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void OnMyTest(FString usn, FString pwd);

};