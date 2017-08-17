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
#include "Animation/AnimNodeBase.h"
#include "LinkerLoad.h"
#include "AnimNode_IKinemaSolver.generated.h"

USTRUCT(BlueprintType)
struct IKINEMACORE_API FAnimNode_IKinemaSolver : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	// The input pose is segmented into two:
	// - The FK input pose that serves as a bias for the solver.
	// - The task targets appended at the end.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink InPose;

	// This is set by the anim graph node, so don't allow further edits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	class UIKinemaRig* IKinemaRig;

	// This is set by the anim graph node, so don't allow further edits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	int32 MaxIteration;

	// The targets for the IKinema solver to try and achieve.
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinShownByDefault))
	TArray<FIKinemaSolverTask> Tasks;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	FIKinemaCOMTask CoMTask;

	// The targets for the IKinema solver to try and achieve.
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	TArray<FIKinemaSolverLookAtTask> LookAtTasks;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinHiddenByDefault))
	TArray<FIKinemaTaskProperties> TaskProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinHiddenByDefault))
	FIKinemaCOMTaskProperties CoMTaskProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, Category=Links)
	TArray<FIKinemaTaskOverride> PinTaskProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinHiddenByDefault))
	TArray<FIKinemaSegmentProperties> SegmentProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, Category=Links)
	TArray<FIKinemaSegmentOverride> PinSegmentProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, Category = Links)
	FIKinemaCOMTaskOverride PinCoMTaskProperties;

	/*
	* Max LOD that this node is running with MaxIteration
	* For example if you have LODHalfThreshold to be 2, it will run until LOD 2 (based on 0 index)
	* when the component LOD becomes 3, it will half the MaxIterations for the solver
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold for Max Iterations"))
	int32 LODHalfThreshold;
	
	/*
	* Max LOD that this node is allowed to run
	* For example if you have LODThreadhold to be 2, it will run until LOD 2 (based on 0 index)
	* when the component LOD becomes 3, it will stop update/evaluate
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))
	int32 LODThreshold;

private:
	bool isBound = false;
	
protected:
	bool bLowestLOD = false;
	bool bIsUpdated = false;
	// Keep the binding here.
	FIKinemaRigToSkeletonBinding mSkeletonBinding;

	// The IKinema solver instance data (solver and tasks).
	FIKinemaSolverInstance mSolverInstance;

	int32	UpdateVersion;
	class UWorld* currentWorld;
	// Ensures the specified object is preloaded.  ReferencedObject can be NULL.
	void PreloadObject(UObject* ReferencedObject);
	bool VRTracked;
public:	
	/**
		Map of LookAtTasks to SolverDefTasks
	*/
	UPROPERTY()
	TArray<int16> LookAtTasksMap;
	FAnimNode_IKinemaSolver();
	virtual ~FAnimNode_IKinemaSolver();

	void Dump(const FString& Folder) const;
	void SetTaskTarget(FIKinemaSolverTask& task, FTransform& animTarget, const FTransform& ToSolverSpace, const FTransform& SolverToWorld, const FIKinemaTaskDef& taskDef, bool drawDebug = true) const;
	// Set the rig on this.
	virtual void SetAsset(class UIKinemaRig* rig);
	virtual void UpdateSolverSettings(class UIKinemaRig* rig);

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;

	void GenerateLookAtTarget(FIKinemaSolverLookAtTask& LookAtTask, const FTransform& animTarget, const FTransform& ToSolverSpace, const int taskIndex);

#if WITH_EDITOR
	bool bEnableDebug = true;			//flag to prevent drawing debug in IKinema Rig - only needed if building with editor 
	void LookAtDebugDraw(const FTransform& SolverToWorld, const FVector& LookAtTarget, const FVector AnimTarget, float& Scale);
	void TaskDebugDraw(const FTransform& SolverToWorld, const FTransform& Target, float& Scale);
	void DrawAllDebug(FPoseContext& Output, FTransform& ToSolverSpace, FTransform& SolverToWorld, FCSPose<FCompactPose>& ComponentSpacePose, FVector* LookAtDirection);
	void IKDebugSphere(const FTransform& SolverToWorld, const FTransform& Target, const float& Scale, const FColor& Colour);
#endif

	/**
		Get the last IKinemaRig version used to set the assets for the Node.
	*/
	const int32 & GetRigVersion() const; 

	bool HasPreUpdate() const override { return true; }

	/** Override this to perform game-thread work prior to non-game thread Update() being called */
	void PreUpdate(const UAnimInstance* InAnimInstance) override;

	// End of FAnimNode_Base interface
};
