#include "WidgetDemo.h"
#include "EventTest.h"

#include "LevelEditorActions.h"
#include "Engine/Selection.h"
#include "Kismet/KismetSystemLibrary.h"

#define LOCTEXT_NAMESPACE "SWidgetdemo"

void SWidgetDemo::Construct(const FArguments& InArgs)
{
	ChildSlot
		.HAlign(HAlign_Left)
		[
			//构造SEventTest的时候，把函数指针传进其构造函数
			SNew(SEventTest).OnStartTest(this, &SWidgetDemo::OnMyTest)
		];
}

void SWidgetDemo::OnMyTest(FString usn, FString pwd)
{
	//FLevelEditorActionCallbacks::SnapObjectToView_Clicked();
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		Actor->Modify();
		FHitResult OutHit;
		RayTracingHit(Actor->GetActorLocation(), FVector(0, 0, -1), 10000.0f, OutHit, Actor);
		FVector HitPointLoc = OutHit.Location + OutHit.ImpactNormal * 0.1f;
		Actor->SetActorLocation(HitPointLoc);
	}
}

bool SWidgetDemo::RayTracingHit(FVector RayOrigin, FVector RayDirection, float RayMarchingLength, FHitResult& OutHitResult, AActor* OperatedActor)
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

#undef LOCTEXT_NAMESPACE