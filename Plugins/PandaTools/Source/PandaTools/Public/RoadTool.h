#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Widgets/Input/SButton.h"

class SRoadTool :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRoadTool){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void OnSliderPointCountChanged(int32 Value);
	void OnSliderSecLengthChanged(float Value);

	TSharedPtr<SButton> ButtonPtr;
	FReply OnGenerateButtonClicked();
	FReply OnResetSplineButtonClicked();

	float RoadSecLength;

private:
	void GenerateSpline();
	bool RayTracingHit(FVector RayOrigin, FVector RayDirection, float RayMarchingLength, FHitResult& OutHitResult, AActor* OperatedActor);
	bool RayTracingHit_Sphere(FVector RayOrigin, FVector RayDirection, float Radius, FHitResult& OutHitResult, AActor* OperatedActor);

};