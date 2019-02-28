#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SPopUI :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPopUI) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	TSharedPtr<IDetailsView> ConfigPanel;
};