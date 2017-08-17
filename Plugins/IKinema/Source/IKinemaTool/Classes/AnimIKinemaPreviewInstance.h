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

#include "Animation/AnimSingleNodeInstance.h"
#include "AnimNode_IKinemaSolver.h"
#include "Animation/AnimSingleNodeInstanceProxy.h"
#include "AnimIKinemaPreviewInstance.generated.h"


/** Proxy override for this UAnimInstance-derived class */
USTRUCT()
struct FAnimIKinemaPreviewInstanceProxy : public FAnimSingleNodeInstanceProxy
{
	GENERATED_BODY()

public:
	FAnimIKinemaPreviewInstanceProxy(): bEnableSolver(false)
	{
		bCanProcessAdditiveAnimations = true;
	}

	FAnimIKinemaPreviewInstanceProxy(UAnimInstance* InAnimInstance)
		: FAnimSingleNodeInstanceProxy(InAnimInstance), bEnableSolver(false)
	{
		bCanProcessAdditiveAnimations = true;
	}

	void Initialize(UAnimInstance* InAnimInstance) override;
	void Update(float DeltaSeconds) override;
	bool Evaluate(FPoseContext& Output) override;

	FAnimNode_IKinemaSolver& GetIKinemaSolver()
	{
		return IKinemaSolver;
	}

	TArray<FIKinemaSolverTask>& GetIKinemaTasks()
	{
		return Tasks;
	}

	TArray<FIKinemaSolverLookAtTask> & GetIKinemaLookAtTasks()
	{
		return LookAtTasks;
	}


	/**
	* Return the task instance to edit, based on the TaskIndex passed in
	* @param   TaskIndex   The index of the task to edit
	* @return  the task instance
	*/
	FIKinemaSolverTask* GetTask(const int& TaskIndex);

	/**
	* Return the Look-At task instance to edit, based on the TaskIndex passed in
	* @param   TaskIndex   The index of the task to edit
	* @return  the Look-At task instance
	*/
	FIKinemaSolverLookAtTask* GetLookAtTask(const int& TaskIndex);

	/**
	* Set the IKinema rig asset in the IKinemaSolver instance
	* @param  InRig  The input rig from the shared data instance
	*/
	void StartTest(UIKinemaRig* InRig);
	
	/**
	* Stop testing the IKinemaRig
	*/
	void EndTest();


private:
	/** IKinema Solver for this Rig */
	FAnimNode_IKinemaSolver IKinemaSolver;

	TArray<FIKinemaSolverTask> Tasks;

	TArray<FIKinemaSolverLookAtTask> LookAtTasks;

	/*
	* Used to determine if controller has to be applied or not
	* Used to disable controller during editing
	*/
	bool bEnableSolver;

	/*
	* Map the rig task index to the look at task index
	*/
	TArray<int16> LookAtTasksMap;
};

/**
 * This Instance only contains one AnimationAsset, and produce poses
 * Used by Preview in AnimGraph, Playing single animation in Kismet2 and etc
 */

UCLASS(transient, NotBlueprintable, noteditinlinenew)
class  UAnimIKinemaPreviewInstance : public UAnimSingleNodeInstance
{
	GENERATED_UCLASS_BODY()

	// Disable compiler-generated deprecation warnings by implementing our own destructor
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
	~UAnimIKinemaPreviewInstance() {}
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

	//~ Begin UObject Interface
	virtual void Serialize(FArchive& Ar) override;
	//~ End UObject Interface

	// Begin UAnimInstance interface
	virtual void NativeInitializeAnimation() override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	// End UAnimInstance interface

	UAnimSequence* GetAnimSequence();

	// Begin UAnimSingleNodeInstance interface
	virtual void SetAnimationAsset(UAnimationAsset* NewAsset, bool bIsLooping = true, float InPlayRate = 1.f) override;
	// End UAnimSingleNodeInstance interface

	/**
	 * Return the task instance to edit, based on the TaskIndex passed in
	 * @param   TaskIndex   The index of the task to edit
	 * @return  the task instance
	*/
	FIKinemaSolverTask* GetTask(const int& TaskIndex);

	/**
	* Return the Look-At task instance to edit, based on the TaskIndex passed in
	* @param   TaskIndex   The index of the task to edit
	* @return  the Look-At task instance
	*/
	FIKinemaSolverLookAtTask* GetLookAtTask(const int& TaskIndex);

	/**
	 * Set the IKinema rig asset in the IKinemaSolver instance
	 * @param  InRig  The input rig from the shared data instance
	 */
	void StartTest(UIKinemaRig* InRig);


	
	/**
	 * Stop testing the IKinemaRig
	 */
	void EndTest();

};



