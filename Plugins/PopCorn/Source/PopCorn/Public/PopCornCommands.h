// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PopCornStyle.h"

class FPopCornCommands : public TCommands<FPopCornCommands>
{
public:

	FPopCornCommands()
		: TCommands<FPopCornCommands>(TEXT("PopCorn"), NSLOCTEXT("Contexts", "PopCorn", "PopCorn Plugin"), NAME_None, FPopCornStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
