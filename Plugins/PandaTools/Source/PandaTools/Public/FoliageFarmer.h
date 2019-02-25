# pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "IDetailRootObjectCustomization.h"
#include "IDetailsView.h"
#include "Engine/EngineTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
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
};

class FMyCustomization:public IDetailCustomization
{
public:
    //IDetailCustomization interface 
    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override; 
    static TSharedRef<IDetailCustomization> MakeInstance();
};

class FRootObjectCustomization:public IDetailRootObjectCustomization 
{
public:
    /**IDetailRootObjectCustomization interface */
    virtual TSharedPtr<SWidget> CustomizeObjectHeader(const UObject* InRootObject) override
    {
        return SNullWidget::NullWidget; 
    }
    virtual bool IsObjectVisible(const UObject* InRootobject) const override { return true;}
    virtual bool ShouldDisplayHeader(const UObject* InRootobject) const override {return false;}
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