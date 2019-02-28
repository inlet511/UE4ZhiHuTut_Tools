// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PopCornCommands.h"

#define LOCTEXT_NAMESPACE "FPopCornModule"

void FPopCornCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "PopCorn", "Execute PopCorn action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
