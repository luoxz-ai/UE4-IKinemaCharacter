/* Copyright 2009-2017 IKinema, Ltd. All Rights Reserved.
*
* IKinema API Library; SDK distribution
*
* This file is part of IKinema RunTime project http://www.ikinema.com
*
* Your use and or redistribution of this software in source and / or binary form, with or without
* modification, is subject to:
* (i) your ongoing acceptance of and compliance with the terms and conditions of
* the IKinema License Agreement; and
*
* (ii) your inclusion of this notice in any version of this software that you use
* or redistribute.
*
*
* A copy of the IKinema License Agreement is available by contacting
* IKinema Ltd., http://www.ikinema.com, support@ikinema.com
*
*/

#pragma once
#include "IKinemaRig.h"
#include "AnimIKinemaPreviewInstance.h"
#include "IKinemaRigToolEdSkeletalMeshComponent.generated.h"


UCLASS()
class UIKinemaRigToolEdSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_UCLASS_BODY()

	/** Data and methods shared across multiple classes */
	class FIKinemaRigToolSharedData* SharedData;

	// Draw colors

	FColor BoneUnselectedColor;
	FColor BoneSelectedColor;
	FColor HierarchyDrawColor;
	FColor AnimSkelDrawColor;
	
	UPROPERTY(transient)
	class UAnimIKinemaPreviewInstance* PreviewInstance;


	/** Mesh-space matrices showing state of just animation (ie before IKinema) - useful for debugging! */
	TArray<FTransform> AnimationSpaceBases;


	/** UPrimitiveComponent interface */
	FPrimitiveSceneProxy* CreateSceneProxy() override;
	
	/** Renders non-hitproxy elements for the viewport, this function is called in the Game Thread */
	virtual void Render(const FSceneView* View, class FPrimitiveDrawInterface* PDI);
	
	/** Renders hitproxy elements for the viewport, this function is called in the Game Thread */
	virtual void RenderHitTest(const FSceneView* View,class FPrimitiveDrawInterface* PDI);

	/** Handles most of the rendering logic for this component */
	void RenderAssetTools(const FSceneView* View, class FPrimitiveDrawInterface* PDI, bool bHitTest);

	/** Draws a constraint */
	void DrawConstraint(int32 ConstraintIndex, const FSceneView* View, FPrimitiveDrawInterface* PDI);

	void DrawLookAtConstraint(int32 ConstraintIndex, FIKinemaTaskDef& task, FTransform& WorldTransforms, FTransform& ComponentTransform, FPrimitiveDrawInterface* PDI);

	/** Draws the CoM constraint */
	void DrawCoMConstraint(const FSceneView* View, FPrimitiveDrawInterface* PDI);

	/** Returns the physics asset for this PhATEd component - note: This hides the implementation in the USkinnedMeshComponent base class */
	class UIKinemaRig* GetIKinemaRig() const;

	void DrawLimits(FPrimitiveDrawInterface* PDI, const FIKinemaTaskDef& task, const FTransform& transform);

	void InitAnim(bool bForceReinit) override;
};
