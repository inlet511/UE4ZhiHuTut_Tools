#include "RoadTool.h"

#include "LevelEditorActions.h"
#include "Engine/Selection.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Layout/SBox.h"

#include "EngineUtils.h"
#include "Road.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

#define LOCTEXT_NAMESPACE "SRoadTools"

void SRoadTool::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			//-------------------------------------------//
			+ SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(120.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("TextDefaultValue0", "SplinePointNum :"))
					]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(60.0f)
					[
						SNew(SSpinBox<int32>)
						.MaxValue(100)
						.MinValue(0)
						.OnValueChanged(this, &SRoadTool::OnSliderPointCountChanged)
					]
				]
			]
			//-------------------------------------------//
			+ SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(60.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("TextDefaultValue1", "SplineSecLength :"))
					]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SSpinBox<float>)
					.MaxValue(200.0f)
					.MinValue(0)
					.OnValueChanged(this, &SRoadTool::OnSliderSecLengthChanged)
				]
			]
			//-------------------------------------------//
			+ SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(120.0f)
					[
						SAssignNew(ButtonPtr, SButton)
						.OnClicked(this, &SRoadTool::OnGenerateButtonClicked)
						.Text(LOCTEXT("Test", "GenerateSpline"))
					]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.HeightOverride(20.0f)
					.WidthOverride(120.0f)
					[
						SAssignNew(ButtonPtr, SButton)
						.OnClicked(this, &SRoadTool::OnResetSplineButtonClicked)
						.Text(LOCTEXT("Test2", "ResetSpline"))
					]
				]
			]
		//---------------------------------------------//
		];
}


void SRoadTool::OnSliderPointCountChanged(int32 Value)
{
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		Actor->Modify();
		ARoad* road = Cast<ARoad>(Actor);
		if (road)
		{
			road->RoadPoints.Init(FVector(0, 0, 0), Value);
		}
	}
}

void SRoadTool::OnSliderSecLengthChanged(float Value)
{
	RoadSecLength = Value;
}

FReply SRoadTool::OnGenerateButtonClicked()
{
	GenerateSpline();
	return FReply::Handled();
}

FReply SRoadTool::OnResetSplineButtonClicked()
{
	GenerateSpline();
	return FReply::Handled();
}

void SRoadTool::GenerateSpline()
{
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		Actor->Modify();
		ARoad* road = Cast<ARoad>(Actor);

		if (road == nullptr) return;
		if (road->RoadPoints.Num() < 1) return;

		//find the first point of spline
		FHitResult hitresult;
		RayTracingHit(road->GetActorLocation(), FVector(0, 0, -1), 100.0f, hitresult, road);
		road->RoadPoints[0] = hitresult.ImpactPoint;
		FVector LastPointLoc = hitresult.ImpactPoint;
		FVector RayStart = hitresult.ImpactPoint;
		FVector LastRayHitNorm = hitresult.ImpactNormal;

		for (int32 i = 1; i < road->RoadPoints.Num(); i++)
		{
			FVector ForwardVec = FVector::CrossProduct(road->GetActorRightVector(), LastRayHitNorm);
			RayStart = ForwardVec * RoadSecLength + LastPointLoc + LastRayHitNorm * 50;

			bool bHit = RayTracingHit(RayStart, -LastRayHitNorm, 100.0f, hitresult, road);
			if (bHit == false)
			{
				RayTracingHit_Sphere(LastPointLoc, -LastRayHitNorm, 100.0f, hitresult, road);
			}


			road->RoadPoints[i] = hitresult.ImpactPoint;
			LastPointLoc = hitresult.ImpactPoint;
			LastRayHitNorm = hitresult.ImpactNormal;

		}
		road->GetRoadSpline()->SetSplinePoints(road->RoadPoints, ESplineCoordinateSpace::World, true);
	}
}

bool SRoadTool::RayTracingHit(FVector RayOrigin, FVector RayDirection, float RayMarchingLength, FHitResult& OutHitResult, AActor* OperatedActor)
{
	const TArray<AActor*> IgnoredActor;
	FVector startPos = RayOrigin;
	FVector endPos = RayOrigin + RayDirection * RayMarchingLength;
	return UKismetSystemLibrary::LineTraceSingle(
		OperatedActor,
		startPos,
		endPos,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		IgnoredActor,
		EDrawDebugTrace::None,
		OutHitResult,
		true,
		FLinearColor::Blue,
		FLinearColor::Red,
		1.0f
	);
}

bool SRoadTool::RayTracingHit_Sphere(FVector RayOrigin, FVector RayDirection, float Radius, FHitResult& OutHitResult, AActor* OperatedActor)
{
	const TArray<AActor*> IgnoredActor;
	FVector endPos = RayOrigin + RayDirection * 100.0f;
	return UKismetSystemLibrary::SphereTraceSingle(
		OperatedActor,
		RayOrigin,
		endPos,
		Radius,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		IgnoredActor,
		EDrawDebugTrace::None,
		OutHitResult,
		true
	);
}

#undef LOCTEXT_NAMESPACE