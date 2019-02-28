// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyStruct.generated.h"

USTRUCT()
struct FMyStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int32 SampleInt32;

	UPROPERTY()
	float Health;

	UPROPERTY()
	AActor* TargetActor;
};