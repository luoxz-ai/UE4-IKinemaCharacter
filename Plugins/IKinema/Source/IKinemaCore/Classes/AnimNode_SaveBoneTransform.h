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
#include "Animation/AnimInstance.h"
#include "AnimNode_SaveBoneTransform.generated.h"

USTRUCT()
struct IKINEMACORE_API FAnimNode_SaveBoneTransform : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink InPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FName PoseName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	TArray<FBoneReference> Bones;
private:
	FA2CSPose CachedPose;
public:	

	FAnimNode_SaveBoneTransform();
	~FAnimNode_SaveBoneTransform();

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	// End of FAnimNode_Base interface
	void InitializeBoneReferences(const FBoneContainer & RequiredBones);
	bool IsValidToEvaluate(const USkeleton * Skeleton, const FBoneContainer & RequiredBones);
};
