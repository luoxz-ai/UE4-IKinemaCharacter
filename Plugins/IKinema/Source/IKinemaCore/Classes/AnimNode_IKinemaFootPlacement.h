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
#include "AnimNode_IKinemaSolver.h"
#include "AnimNode_IKinemaFootPlacement.generated.h"

UENUM()
namespace ELimitAxisOption
{
	enum Type
	{
		X,
		Y,
		Z
	};
}

UENUM()
namespace EAimingOptions
{
	enum Type
	{
		SingleHand UMETA(DisplayName = "Single Hand Wield", ToolTip = "Holding a single weapon (e.g. Pistol)"), 
		TwoHand  UMETA(DisplayName = "Two Hand Wield", ToolTip = "Holding a single weapon with two hands(e.g. Rifle, Bow)"),
		DualWield UMETA(DisplayName = "Dual Wield", ToolTip = "Holding a two weapon (e.g. Pistol)")
	};
}

UENUM()
namespace EShape
{
	enum Type
	{
		Line,
		Box,
		Sphere,
		Capsule
	};
}

USTRUCT(BlueprintType)
struct FLimbBone 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, /*BlueprintReadWrite,*/ Category = Collision)
	FBoneReference Bone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	TEnumAsByte<enum EShape::Type> Shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	FVector Extents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	FTransform Offset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	bool DrawDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (ToolTip = "Allows user to set custom scale for the start and end positions of the line trace"))
	bool UseCustomScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (ToolTip = "Scale the global starting position of the line trace. By default, the length is equal to the Capsule Half Height"))
	float CustomRayTraceStartScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (ToolTip = "Scale the global starting position of the line trace. By default, the length is equal to the Capsule Half Height"))
	float CustomRayTraceFinishScale;

	FCollisionShape CollisionShape;
};


USTRUCT()
struct IKINEMACORE_API FAnimNode_IKinemaFootPlacement : public FAnimNode_IKinemaSolver
{
	GENERATED_USTRUCT_BODY()

		/** Enum indicating the collision channel to use when casting rays */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		TEnumAsByte<enum ECollisionChannel> CollisionChannel;

		/** If EffectorTransformSpace is a bone, this is the bone to use. **/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EndEffector, meta = (NeverAsPin))
		TArray<FLimbBone> LimbTransforms;

		/** The name of the bone attached to the weapon handle. **/
		UPROPERTY( EditAnywhere, /*BlueprintReadWrite,*/ Category = EndEffector, meta = (NeverAsPin))
		FBoneReference HandleBone;

		/** The name of the bone attached to the weapon trigger. **/
		UPROPERTY(EditAnywhere, /*BlueprintReadWrite, */ Category = EndEffector, meta = (NeverAsPin))
		FBoneReference TriggerBone;

		UPROPERTY(EditAnywhere, /*BlueprintReadWrite,*/ Category = EndEffector, meta = (NeverAsPin))
		FBoneReference HipsTransform;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset , meta = (PinShownByDefault))
		TArray<float> MeshOffset;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault))
		TArray<float> Alpha;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault))
		float MaxHipMultiplier;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault))
		float MinHipMultiplier;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (ToolTip = "Scale the global starting position of the line trace. A Value of 1 corresponds to a length equal to Capsule Half Height"))
		float GlobalRayTraceStartScale;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (ToolTip = "Scale the global finishing position of the line trace. A Value of 1 corresponds to length equal to Capsule Half Height"))
		float GlobalRayTraceFinishScale;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault, ToolTip = "Upperbody offset in Component Space"))
		FVector UpperBodyOffset;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinHiddenByDefault))
		FVector lookAtDirection;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))
		FVector HandleOffset;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))
		bool AimWithWeapon;
		
		/** Whether we should trace against complex collision */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		bool bTraceComplex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))
		TEnumAsByte<enum EAimingOptions::Type> AimingType;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))
		bool LockFreeArm;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault))
		bool bReverseFootSetup;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault))
		float ReverseFootFactor;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset)
		float RollLimit;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset)
		float PitchLimit;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Smoothness, meta = (DisplayName = "Position Blend Speed", ToolTip = "Speed of change in task position when smoothing"))
		float PTransitionSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Smoothness, meta = (DisplayName = "Rotation Blend Speed", ToolTip = "Speed of change in task rotation when smoothing"))
		float RTransitionSpeed;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Smoothness, meta = (DisplayName = "Maximum step change", ToolTip = "If change in hit location greater than this value, do not smooth the task demands"))
		float PTransitionMaxDistance;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))
		float LookAtAlpha;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))
		float LookAtSmoothness;

		/** Flag to show and use the generic solver task inputs along with the foot placement logic */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset)
		bool ExposeSolverTasks;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt)
		bool InComponentSpace;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt)
		bool ReduceWeight;

		/** Whether or not to use Up axis */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt)
		bool UseLookUpAxis;

		/** Up axis in local space */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt)
		TEnumAsByte<ELimitAxisOption::Type>	LookUpAxis;
		/** Look at limit value in degree - limit the rotation around the look at axis*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt)
		FRotator lookAtLimit;

		/** Look at Clamp value in degree - if you're look at axis is Z, only X, Y degree of clamp will be used*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinHiddenByDefault))
		float LookAtClamp;

//#if IKINEMA_WITH_SE	
		/** Look at Clamp value in degree - if you're look at axis is Z, only X, Y degree of clamp will be used*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinHiddenByDefault))
		bool LimitsInParentSpace;
//#endif
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset, meta = (PinShownByDefault))
		bool bFloorContact;

		//Enable to draw debug for ALL tasks in the Rig. 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool DrawDebug;

		//TestOption
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		bool bFootStabilization;

		//Multiplies by foot bone length to give threshold for foot stabilization
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		float StabilizationThreshold;

//#if WITH_EDITOR
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		float GlobalDebugScale;
//#endif

public:
	// FAnimNode_Base interface
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	// End of FAnimNode_Base interface

protected:
	//Hold task current and previous task targets
	TArray<FTransform> TaskTargets;
	int TriggerHandTaskIndex;
	int HandleHandTaskIndex;
private:
	TArray<FVector> PrevNormal;
	TArray<FVector> PrevTarget;
	float interp;
#if IKINEMA_WITH_SE
	FVector PrevLookAt;
	bool SwitchedSide;
#endif

protected:
	bool DoRayTrace(const USkeletalMeshComponent* mesh, FTransform& transform, const FTransform& SolverToWorld, const int index);
	
#if WITH_EDITOR
	void RayTraceDebugDraw(const FLimbBone& LimbTransform, FVector& p, FVector& upTraceDirection, FVector& downTraceDirection, FHitResult& OutHit, FTransform& ShapeOffset, bool bHit);
#endif

	void ReverseFootSetup(const FCompactPose& pose, USkeletalMeshComponent const* mesh, FCSPose<FCompactPose>& ComponentSpacePose, const FTransform& SolverToWorld);
	void PassTargetsToTasks(FCSPose<FCompactPose>& ComponentSpacePose, FTransform& SolverToWorld, FTransform& ComponentToWorld, FVector& avr);

	FQuat GenerateLookAtTarget(FVector targetLocation, const FTransform& animTarget, const FTransform& parentRot, const int taskIndex, const FTransform& ComponentToSolverSpace);
	FQuat GenerateLookAtTarget(FVector targetLocation, const FTransform& animTarget, const int taskIndex, const FTransform& ComponentToSolverSpace, const FTransform& SolverToWorld);

	FVector FootStabilization(const FCompactPose& pose, FCSPose<FCompactPose>& ComponentSpacePose, const FTransform& SolverToWorld, const FTransform& ComponentToWorld, TArray<FVector>& worldNormalArray, TArray<FVector>& worldPosArray, const FTransform& ComponentToSolverSpace);

	// Copied from FAnimNode_SkeletalControlBase interface
	bool IsValidToEvaluate(const USkeleton * Skeleton, const FBoneContainer & RequiredBones);
	void InitializeBoneReferences(const FBoneContainer & RequiredBones);
	// End of FAnimNode_SkeletalControlBase interface

public:
	FAnimNode_IKinemaFootPlacement();
	~FAnimNode_IKinemaFootPlacement();

	// Set the rig on this.
	void SetAsset(class UIKinemaRig* rig) override;
	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	// End of FAnimNode_Base interface
};
