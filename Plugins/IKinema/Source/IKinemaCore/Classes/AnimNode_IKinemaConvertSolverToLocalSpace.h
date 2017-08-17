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
#include "Animation/AnimNodeBase.h"
#include "IKinemaRig.h"
#include "LinkerLoad.h"
#include "AnimNode_IKinemaConvertSolverToLocalSpace.generated.h"


USTRUCT()
struct IKINEMACORE_API FAnimNode_IKinemaConvertSolverToLocalSpace : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	// The input pose is segmented into two:
	// - The FK input pose that serves as a bias for the solver.
	// - The task targets appended at the end.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink InPose;

	// This is set by the anim graph node, so don't allow further edits.
	UPROPERTY()
	class UIKinemaRig* IKinemaRig;
/*
	UPROPERTY(transient)
	int32 LastFrameUpdated;

	UPROPERTY(transient)
	int32 LastFrameEvaluated;
*/
protected:
	// Keep the binding here.
	FIKinemaRigToSkeletonBinding mSkeletonBinding;

	// Ensures the specified object is preloaded.  ReferencedObject can be NULL.
	static void PreloadObject(UObject* ReferencedObject)
	{
		if ((ReferencedObject != nullptr) && ReferencedObject->HasAnyFlags(RF_NeedLoad))
		{
			ReferencedObject->GetLinker()->Preload(ReferencedObject);
		}
	}
public:	

	FAnimNode_IKinemaConvertSolverToLocalSpace();
	~FAnimNode_IKinemaConvertSolverToLocalSpace();

	// Set the rig on this.
	virtual void SetAsset(class UIKinemaRig* rig);

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	// End of FAnimNode_Base interface
};
