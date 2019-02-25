// Fill out your copyright notice in the Description page of Project Settings.

#include "Road.h"
#include "Components/SplineComponent.h"

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	rotComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = rotComp;

	RoadSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RoadSplineMeshComponent"));
	RoadSpline->SetSplinePoints(RoadPoints, ESplineCoordinateSpace::Local, true);
	RoadSpline->bDrawDebug = true;
	RoadSpline->SetupAttachment(GetRootComponent());

}



