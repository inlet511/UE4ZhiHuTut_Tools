// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

UCLASS()
class PANDATOOLS_API ARoad : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Road", meta = (AllowPrivateAccess="true"))
	class USceneComponent* rotComp;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Road", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* RoadSpline;
	
public:	
	// Sets default values for this actor's properties
	ARoad();
	
	TArray<FVector> RoadPoints;

	class USplineComponent* GetRoadSpline() { return RoadSpline; }

};
