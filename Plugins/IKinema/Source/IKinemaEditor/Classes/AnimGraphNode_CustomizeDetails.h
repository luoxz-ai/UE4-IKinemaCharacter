#include "IPropertyTypeCustomization.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "DetailCategoryBuilder.h"
#pragma once

class FAnimNode_IKinemaSolverPropTypeCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
};

/*
Class for customizing the details panel of the solver nodes.
*/

class FAnimNode_IKinemaSolverLayoutDetails : public IDetailCustomization
{
public:
	/*IDetailCusomisation interface*/
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	//Combo button menu set up
	void MakeComboButton(IDetailCategoryBuilder& InCategory, TSharedPtr <IPropertyHandle> NamePropertiesHandle, TSharedPtr <IPropertyHandle> TaskPropertiesHandle, FName TaskOrBone);
	TSharedRef<SWidget> GetTaskMenuContent(TSharedPtr <IPropertyHandle> TaskPropertyHandle, TSharedPtr <IPropertyHandle> TaskPropertiesHandle, FName TaskOrBone) const;
	FText GetCurrentTaskMenuListing(TSharedPtr <IPropertyHandle> TaskPropertyHandle, FName TaskOrBone) const;
	void OnTaskMenuListingChange(int32 Selection, TSharedPtr <IPropertyHandle> PropertyHandle, FName TaskOrBone);
	

	IDetailLayoutBuilder* MyDetailLayout;

	//Handles to indicies stored in AnimGraphNode_Ikinemasolver/FootPlacement and fetched in order to switch selected task/bone in combo buttons
	TSharedPtr<IPropertyHandle> TaskSelectionHandle;
	TSharedPtr<IPropertyHandle> BoneSelectionHandle;

	//populating category functions
	void PopulateGeneralSettingsCat(TSharedRef <IPropertyHandle> ParentPropertyHandle, IDetailCategoryBuilder& GeneralSettingsCat);
	void AddPinToCat(FName BoneOrTask, TSharedPtr <IPropertyHandle> PropertiesHandle, IDetailCategoryBuilder& InCategory);

	void PopulateCategories(TSharedPtr <IPropertyHandle> PropertiesHandle, IDetailCategoryBuilder& InCategory, uint32 Element);

	//Handling displaying FVector UProperties
	void HandleVectorProperties(TSharedPtr<IPropertyHandle> GreatGrandChildHandle, IDetailCategoryBuilder& TaskPropertiesCat);

	//index to specify which task/bone to populate the settings menu for
	UPROPERTY()
	int32 TaskSelectionNo = 0;
	UPROPERTY()
	int32 BoneSelectionNo = 0;
};
