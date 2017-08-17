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
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "IKinemaRTAnimInstance.generated.h"

USTRUCT() 
struct FIKinemaSavedPose
{
	GENERATED_BODY()
	TArray<FTransform> BoneArray;
	FBoneContainer BoneContainer;
};

USTRUCT()
struct FIKinemaRTAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

public:
	FIKinemaRTAnimInstanceProxy();
	FIKinemaRTAnimInstanceProxy(UAnimInstance* Instance);

	void GetBoneFromPose(const FName& SavedPose, const FName& BoneName, /*FName NotifierName, */bool ForceUpdate, FTransform& BoneTransform_) const;

public:
	TMap<FName, FIKinemaSavedPose> SavedPoses;

};

/**
 * 
 */
UCLASS(Transient, Blueprintable)
class IKINEMACORE_API UIKinemaRTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;

public:
	
	void GetBoneFromPose (const FName& SavedPose, const FName& BoneName, bool ForceUpdate, FTransform& BoneTransform) const;
private:
	friend struct FIKinemaRTAnimInstanceProxy;
	
	
};
