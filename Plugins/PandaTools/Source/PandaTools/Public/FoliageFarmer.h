# pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "IDetailRootObjectCustomization.h"
#include "IDetailsView.h"
#include "Engine/EngineTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EdGraph/EdGraph.h"
#include "GraphEditor.h"
#include "FoliageFarmer.generated.h"

DECLARE_DELEGATE(FSFoligeFarmerBackToMainUI);

class FMyCustomization;
class AMyClass;

class SFoliageFarmer: public SCompoundWidget
{
public: 
    SLATE_BEGIN_ARGS(SFoliageFarmer){}
    SLATE_EVENT(FSFoligeFarmerBackToMainUI, EventDelegate_BackToMainUI)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    TSharedPtr<IDetailsView> ConfigPanel;

private:
	UEdGraph* GraphObj;
	TSharedPtr<SGraphEditor> GraphEditorPtr;
};

class FMyCustomization:public IDetailCustomization
{
public:
    //IDetailCustomization interface 
    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override; 
    static TSharedRef<IDetailCustomization> MakeInstance();
};


UCLASS()
class UMyClass:public UObject 
{
	GENERATED_BODY()

	class UTexture2D;
	class UMaterial;
public: 
    UPROPERTY(EditAnywhere,category="Test")
    float TestFloat; 
    
    UPROPERTY(EditAnywhere,category="Test")
    UTexture2D* TestTexture; 
    
    UPROPERTY(EditAnywhere,Category="Test02")
    UMaterial* TestMaterial;

	FReply TestClicked();
};