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
#include "IKSolver.h"
#include "IKTask.h"

#include "IKinemaRig.generated.h"


UENUM()
namespace EIKinemaBoneAxisType
{
	
	enum Type
	{
		EIKBAT_X,
		EIKBAT_Y,
		EIKBAT_Z,
	};
}

/** Enum for controlling which reference frame a controller is applied in. */
UENUM()
namespace EIKinemaTargetType
{

	enum Type
	{
		BlendToTarget UMETA(DisplayName = "Blend to target", ToolTip = "Blend away from original animation towards the target"),
		BlendWithTarget UMETA(DisplayName = "Blend animation with target", ToolTip = "Blend towards the target, while preserving subtle animation details"),
		BlendWithOffset UMETA(DisplayName = "Target is offset to animation", ToolTip = "Target is offset added to animation")
	};
}

USTRUCT()
struct FIKinemaLookAtLimits
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = LookAt)
	FRotator Min;

	UPROPERTY(EditAnywhere, Category = LookAt)
	FRotator Max;

};

USTRUCT()
struct FIKinemaEulerLimits
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category=Advanced)
	FVector MinDegrees;

	UPROPERTY(EditAnywhere, Category=Advanced)
	FVector MaxDegrees;

	/*
	Axis along the bone
	*/
	UPROPERTY(EditAnywhere, Category = Advanced)
	TEnumAsByte<EIKinemaBoneAxisType::Type> BoneAxis;

	// Set to default values..
	void InitializeValues();
};

USTRUCT()
struct IKINEMACORE_API FIKinemaBoneDef
{
	GENERATED_USTRUCT_BODY()

	~FIKinemaBoneDef();


	/*
	Name of selected bone. 
	*/
	UPROPERTY(VisibleAnywhere, Category="General Bone Settings")
	FName	Name;

	/*
	Name of parent bone.
	*/
	UPROPERTY(VisibleAnywhere, Category="General Bone Settings")
	FName	ParentName;

	/*
	Disables the bone inside the IKinema solver
	*/
	UPROPERTY(EditAnywhere, Category = "General Bone Settings")
	bool	Active;

	/*
	Enable or disable X-Axis degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings", DisplayName = "DoF X", meta=(EditCondition = "Active"))
	bool	DofX;

	/*
	Enable or disable Y-Axis degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings", DisplayName = "DoF Y", meta = (EditCondition = "Active"))
	bool	DofY;

	/*
	Enable or disable Z-Axis degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings", DisplayName = "DoF Z", meta = (EditCondition = "Active"))
	bool	DofZ;

	/*
	The rotational mobility of the bone. A value of 1 means the bone is very mobile. A value of
	0 means the bone is effectively disabled.
	*/
	UPROPERTY(EditAnywhere, Category = "General Bone Settings", meta = (EditCondition = "Active"))
	FVector	Weight;


	/*
	The mass of the bone. Fetched from the physics asset or assigned by hand.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings", meta = (EditCondition = "Active"))
	float	Mass; 

	/*
	Enables resetting the bone to its reference pose transform at the start of each solve.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings", meta = (EditCondition = "Active"))
	bool	ResetToRest;

	/*
	If enabled, the input animation influences the output of the solver. If disabled, does not.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings", meta = (EditCondition = "Active"))
	bool	EnableRetargeting;

	/*
	Influence the input animation will have on final pose. 
	*/
	UPROPERTY(EditAnywhere, Category = "General Bone Settings", meta = (EditCondition = "Active"))
	float	RetargetingGain;

	/*
	Acts as a multiplier to the 'retargeting gain' along specific axis (in bone local space).
	*/
	UPROPERTY(EditAnywhere, Category = "General Bone Settings", DisplayName = "Retargeting DoF Gain", meta = (EditCondition = "Active"))
	FVector	RetargetingDoFGain;


	/*
	The maximal rotation velocity allowed for the bone per frame. Increase this value if the solver output is lagging behind the
	input FK animation.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "General Bone Settings")
	float	MaxVelocity;


	/*
	Enable or disable X-Axis degree of freedom for StretchIK
	*/
	UPROPERTY(EditAnywhere, Category = "StretchIK Settings", DisplayName = "Enable Stretch Along X")
	bool	StretchX = false;

	/*
	Enable or disable Y-Axis degree of freedom for StretchIK
	*/
	UPROPERTY(EditAnywhere, Category = "StretchIK Settings", DisplayName = "Enable Stretch Along Y")
	bool	StretchY = false;

	/*
	Enable or disable Z-Axis degree of freedom for StretchIK
	*/
	UPROPERTY(EditAnywhere, Category = "StretchIK Settings", DisplayName = "Enable Stretch Along Z")
	bool	StretchZ = false;

	/*
	The translational mobility of the bone. A value of 1 gives high translational mobility. A value of 0 disables translational mobility.
	*/
	UPROPERTY(EditAnywhere, Category = "StretchIK Settings")
	FVector	StretchWeight;


	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "StretchIK Settings")
	bool	EnableStretchLimits = false;


	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "StretchIK Settings")
	bool	EnforceStretchLimits = false;


	UPROPERTY()
	float StretchErrorGain = 1.f;

	/*
	Index of the task that drives this bone or INDEX_NONE (reverse lookup of FIKinemaTaskDef::BoneIndex)
	*/
	UPROPERTY()
	int32	TaskIndex;

	/*Index of the parent bone or INDEX_NONE (derived from ParentName)
	*/
	UPROPERTY()
	int32	ParentIndex;

	/*
	Enable or disable enforcing limits in the range of rotation for selected bone.
	*/
	UPROPERTY(EditAnywhere, Category = "Limits")
	bool	EnableLimits;

	/*
	Set the rotation limit for selected bone in degrees. 
	*/
	UPROPERTY(EditAnywhere, Category = "Limits", meta=(EditCondition = "EnableLimits"))
	FIKinemaEulerLimits Limits;

	/*
	Always pulls the bone towards the central point of the range specified as limits.
	*/
	UPROPERTY(EditAnywhere, Category = "Limits", meta = (EditCondition = "EnableLimits"))
	bool	EnforceLimits;

	/*
	The importance assigned to enforcing the set limits. A value of 0 disables the limits, a value of 1 tries to enforce them.
	*/
	UPROPERTY(EditAnywhere, Category = "Limits", meta = (EditCondition = "EnableLimits"))
	float	LimitsGain;

	UPROPERTY()
	FTransform	RestPose;

	//Constructor
	FIKinemaBoneDef();

	// Set to default values..
	void InitializeValues();

	void PostLoadOrImport();

#if WITH_EDITOR
	void CopyBoneDefPropertiesFrom(FIKinemaBoneDef const* other);

	void CopyBoneDefPropertiesFrom(FIKinemaBoneDef const& other);

	void ResetToDefaults();
#endif

	// Bind to the given skeleton
	bool BindToSkeleton(FIK::ImportBone& importBone, USkeleton& skeleton, int32& ue4BoneIndex, bool upY, USkeletalMeshComponent* component);

	// Configure an IKinema bone segment (inside the solver instance).
	void ConfigureIKSegment(FIK::IKSegment& segment) const;

	// Transfer an IKinema pose to a UE4 pose, for this bone.
	void IKinemaToUE4Pose(const FIK::IKSegment& segment, FTransform& ue4Transform, bool applyTranslation) const;

private:

	// Cache ANSI names from the wide versions.
	void CacheANSINames();

	// Cache the ANSI version of the name and parent name.
	static const int32 MAX_NAME_LENGTH = 512;
	ANSICHAR mNameANSI[MAX_NAME_LENGTH];
	ANSICHAR mParentNameANSI[MAX_NAME_LENGTH];
};

USTRUCT()
struct IKINEMACORE_API FIKinemaTaskDef
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = "General Task Settings")
	FName	Name;

	/*
	Enable or disable position task
	*/
	UPROPERTY(EditAnywhere, Category="General Task Settings")
	bool	HasPositionTask;

	/*
	Enable or disable rotation task
	*/
	UPROPERTY(EditAnywhere, Category = "General Task Settings", DisplayName = "Has Orientation Task")
	bool	HasRotationTask;

	/*
	Mark this task as VR specific
	*/
	UPROPERTY(EditAnywhere, Category = "General Task Settings", DisplayName = "VR Task")
	bool bIsVRTask = false;

	/*
	Motion controller offset.
	*/
	UPROPERTY(EditAnywhere, Category = "General Task Settings", DisplayName = "VR Controller Offset", meta = (EditCondition = "bIsVRTask"))
	FTransform MCOffset;	

	UPROPERTY(Transient)
	UStaticMeshComponent* MotioncController;

	UPROPERTY()
	bool	RootAsScalePivot;

	/* 
	Index of the FIKinemaBoneDef that is being driven by this task.
	*/
	UPROPERTY()
	int32	BoneIndex;

	/*
	Index of the parent task or INDEX_NONE (derived by walking up the bone hierarchy to find the first parent that has a corresponding task).
	*/
	UPROPERTY()
	int32	ParentIndex;

	/*
	Enable or disable this task as a pole vector task. 
	*/
	UPROPERTY(EditAnywhere, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"), DisplayName = "Enable As Pole Vector")
	bool PositionAsPoleObject;

	/*
	The position (in bone local space) of pole vector task.
	*/
	UPROPERTY(EditAnywhere, Category = "PositionTask", meta = (EditCondition = "PositionAsPoleObject")) //"HasPositionTask"))
	FVector PoleVectorLocalSpace; 

	/*
	Enable or disable the X-Axis translational degree of freedom 
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"))
	bool PositionDofX;

	/*
	Enable or disable the Y-Axis translational degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"))
	bool PositionDofY;

	/*
	Enable or disable the Z-Axis translational degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"))
	bool PositionDofZ;

	/*
	The distance (in number of bones) the effect of this task reaching its target position will have an influence.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"))
	uint32 PositionDepth;

	/*
	The weighting assigned to this task in achieving its target position relative to other tasks. Higher weight translates 
	to higher priority. 
	*/
	UPROPERTY(EditAnywhere, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"))
	FVector PositionWeight;

	/*
	Recommended values between 2-4.
	*/
	UPROPERTY(EditAnywhere, Category = "PositionTask", meta = (EditCondition = "HasPositionTask"))
	FVector PositionPrecision;

	UPROPERTY()
	uint32 PositionPriority;

	UPROPERTY()
	FVector ScaleRetargeting;

	UPROPERTY()
	FVector OffsetRetargeting;

	/*
	Enable or disable the X-Axis rotation degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "OrientationTask", meta = (EditCondition = "HasRotationTask"))
	bool RotateDofX;

	/*
	Enable or disable the Y-Axis rotation degree of freedom 
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "OrientationTask", meta = (EditCondition = "HasRotationTask"))
	bool RotateDofY;

	/*
	Enable or disable the Z-Axis rotation degree of freedom
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "OrientationTask", meta = (EditCondition = "HasRotationTask"))
	bool RotateDofZ;

	/*
	The distance (in number of bones) the effect of this task reaching its target rotation will have an influence.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "OrientationTask", meta = (EditCondition = "HasRotationTask"))
	uint32 RotateDepth;
	
	/*
	The weighting assigned to this task in achieving its rotation target relative to other tasks. Higher weight translates
	to higher priority.
	*/
	UPROPERTY(EditAnywhere, Category = "OrientationTask", meta = (EditCondition = "HasRotationTask"))
	FVector RotateWeight;

	/* 
	Recommended values between 2-4.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "OrientationTask", meta = (EditCondition = "HasRotationTask"))
	FVector RotatePrecision;

	UPROPERTY()
	uint32 RotatePriority;

	/*
	Enables or disables this task being treated as a look-at task.
	*/
	UPROPERTY(EditAnywhere, Category = "OrientationTask:LookAt", meta = (EditCondition = "HasRotationTask"))
	bool LookAt;

	UPROPERTY()
	bool IsChest;
	
	/*
	Tick for look at axis in local space.
	Untick for look at axis in component space.
	*/
	UPROPERTY(EditAnywhere, Category = "OrientationTask:LookAt", DisplayName = "Use Local Space Axis For Look At", meta = (EditCondition = "LookAt"))
	bool UseLocalSpace;

	/*
	Look at axis in local space
	*/
	UPROPERTY(EditAnywhere, Category = "OrientationTask:LookAt", DisplayName = "Look At Axis (Local Space)", meta = (EditCondition = "UseLocalSpace"))
	FVector TipOffsetLocal;

	/*
	Look at axis in component space
	*/
	UPROPERTY(EditAnywhere, Category = "OrientationTask:LookAt", DisplayName = "Look At Axis (Component Space)", meta= (EditCondition = "!UseLocalSpace"))
	FVector TipOffset;

	UPROPERTY(EditAnywhere, Category = "OrientationTask:LookAt", meta = (EditCondition = "HasRotationTask"))
	FIKinemaLookAtLimits LookAtLimits;

	// Set to default values..
	void InitializeValues();

#if WITH_EDITOR
	void CopyTaskDefPropertiesFrom(FIKinemaTaskDef const* other);
	
	void CopyTaskDefPropertiesFrom(FIKinemaTaskDef const& other);

	void ResetToDefaults();
#endif

	UPROPERTY()
	bool IsRightHand = false;

	UPROPERTY()
	bool IsLeftHand = false;

	void PostLoadOrImport();

	// Configure a position task using our properties.
	void ConfigurePositionTask(FIK::IKPositionTask& positionTask) const;

	// Configure an orientation task using our properties.
	void ConfigureOrientationTask(FIK::IKOrientationTask& orientationTask) const;
};

USTRUCT()
struct FIKinemaForceDef
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category=IKDefinition)
	FName		Name;

	UPROPERTY(EditAnywhere, Category=IKDefinition)
	uint32		BoneIndex;

	UPROPERTY(EditAnywhere, Category=IKDefinition)
	bool		Support;

	UPROPERTY(EditAnywhere, Category=IKDefinition)
	float		SupportRatio;

	UPROPERTY(EditAnywhere, Category=IKDefinition)
	FVector		Force;

	UPROPERTY(EditAnywhere, Category=IKDefinition)
	FVector		WorldForce;

	// Set to default values..
	void InitializeValues();
};

USTRUCT()
struct IKINEMACORE_API FIKinemaCOMDef
{
	GENERATED_USTRUCT_BODY()

	/*
	Enable or disable the X-Axis degree of freedom for driving the CoM
	*/
	UPROPERTY(EditAnywhere, Category = "Centre Of Mass Task", DisplayName = "CoM DoF X")
	bool DegreeOfFreedomX;

	/*
	Enable or disable the Y-Axis degree of freedom for driving the CoM
	*/
	UPROPERTY(EditAnywhere, Category = "Centre Of Mass Task", DisplayName = "CoM DoF Y")
    bool DegreeOfFreedomY;

	/*
	Enable or disable the Z-Axis degree of freedom for driving the CoM
	*/
	UPROPERTY(EditAnywhere, Category = "Centre Of Mass Task", DisplayName = "CoM DoF Z")
	bool DegreeOfFreedomZ;

	/*
	The weighting assigned to the centre of mass task reaching its target position relative to other tasks.
	A higher weighting translates to a higher priority.
	*/
	UPROPERTY(EditAnywhere, Category = "Centre Of Mass Task", DisplayName = "CoM Task Weight")
	FVector Weight;

	/*
	Recommended values between 2 - 4.
	*/
	UPROPERTY(EditAnywhere, Category = "Centre Of Mass Task", DisplayName = "CoM Task Precision")
	FVector Precision;

	// Set to default values..
	void InitializeValues();

	// Configure the task using our properties.
	void ConfigureTask(FIK::IKBalanceTask& task) const;

#if WITH_EDITOR
	void CopyTaskDefPropertiesFrom(FIKinemaCOMDef const* other);

	void CopyTaskDefPropertiesFrom(FIKinemaCOMDef const& other);

	void ResetToDefaults();
#endif

};

USTRUCT()
struct FIKinemaSolverDef
{
	GENERATED_USTRUCT_BODY()

	/*
	The maximum number of iterations the IKinema solver will perform before it outputs a solution.
	30 is recommended for general purpose use.
	*/
	UPROPERTY(EditAnywhere, Category= "IKinema Solver - General Settings")
	int32 MaxIterations;

	UPROPERTY()
	FName UpAxis;

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "IKinema Solver - General Settings")
	float LimitsGain;

	/*
	Recommended values between 2 - 4
	*/
	UPROPERTY(EditAnywhere, Category = "IKinema Solver - General Settings", DisplayName = "Global Tasks Precision")
	float TasksPrecision;

	/*
	Global Retargeting Gain Multiplier.
	*/
	UPROPERTY(EditAnywhere, Category = "IKinema Solver - General Settings", DisplayName = "Global Retargeting Gain")
	float RetargetingGain;

	/*
	IKinema Solver Parameter. Enable 'Auto Tune' below to automatically set this value.
	*/
	UPROPERTY(EditAnywhere, Category = "IKinema Solver - General Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float PCoefficient;

	/*
	Enable to automatically set the solver P-Coefficient
	*/
	UPROPERTY(EditAnywhere, Category = "IKinema Solver - General Settings")
	bool AutoTune;

	/*
	If the difference between the current location of a bone and its target position is less than this value, the solver
	will return the solved pose early, before it reaches the maximum iteration limit.
	*/
	UPROPERTY()
	float SolutionTolerance;

	/*
	Enable root motion.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "IKinema Solver - General Settings")
	bool TranslateRoot;

	/*
	Enable or disable the X-Axis translational degree of freedom for the Root bone. 
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "IKinema Solver - General Settings", DisplayName = "Root Translation DoF X", meta = (EditCondition = "TranslateRoot") )
	bool RootTranslationDofX;

	/*
	Enable or disable the Y-Axis translational degree of freedom for the Root bone.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "IKinema Solver - General Settings", DisplayName ="Root Translation DoF Y", meta = (EditCondition = "TranslateRoot"))
	bool RootTranslationDofY;

	/*
	Enable or disable the Z-Axis translational degree of freedom for the Root bone.
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "IKinema Solver - General Settings", DisplayName = "Root Translation DoF Z", meta = (EditCondition = "TranslateRoot"))
	bool RootTranslationDofZ;

	/*
	Influence the other tasks will have in root translation
	*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "IKinema Solver - General Settings", meta = (EditCondition = "TranslateRoot"))
	float RootTranslationWeight;

	UPROPERTY()
	FVector RootTargetTranslation;

	/*
	Enable/Disable centre of mass task.
	*/
	UPROPERTY(EditAnywhere, Category = "IKinema Balance Task", meta = (EditCondition = "SwitchBalanceTask"))
	bool ActiveCOM;

	/*
	Mass of entire skeleton.
	*/
	UPROPERTY(EditAnywhere, Category = "IKinema Balance Task", meta = (EditCondition = "SwitchBalanceTask"))
	float FigureMass;

	UPROPERTY(EditAnywhere, Category = "IKinema Balance Task", DisplayName = "CoM Properties", meta = (EditCondition = "SwitchBalanceTask"))
	struct FIKinemaCOMDef COM;

	///Moments functionality to be added in future update
	UPROPERTY()
	bool EnableMoments;

	UPROPERTY()
	bool UseDefaultZMP;

	UPROPERTY()
	FVector ZeroMomentPoint;

	UPROPERTY()
	float MomentsWeight;

	UPROPERTY()
	float MomentsPriority;

	UPROPERTY()
	bool ContinuouslySolving;

	UPROPERTY()
	float PoseTolerance;

	UPROPERTY()
	bool Retargeting;

	UPROPERTY()
	FVector RetargetingTaskScale;

	UPROPERTY()
	FVector RetargetingTaskOffset;

	UPROPERTY()
	bool EnableRootTargetTranslation;

	UPROPERTY()
	bool RescaleTasks;

	UPROPERTY()
	float SecondaryTaskWeight;

	UPROPERTY()
	float SecondaryTaskPrecision;

	UPROPERTY( EditAnywhere, Category = IKDefinition)
	TArray<struct FIKinemaBoneDef> Bones;

	UPROPERTY(EditFixedSize, EditAnywhere, Category=IKDefinition)
	TArray<struct FIKinemaTaskDef> Tasks;

	UPROPERTY(EditFixedSize, EditAnywhere, Category=IKDefinition)
	TArray<struct FIKinemaForceDef> Forces;

	// Reset to default values.
	void InitializeValues();

	// Configure the given solver using our properties.
	bool ConfigureSolver(class FIKinemaSolverInstance& solverInstance) const;

	bool ApplySettings(class FIKinemaSolverInstance& solverInstance) const;

	// Called from the outer rig class.
	void PostLoadOrImport();

	void ClearDefinition();

	// Find the index of the task with the given name in our list.
	// Returns INDEX_NONE if not found.
	IKINEMACORE_API int32 FindTaskIndex(const FName& taskName) const;

	// Find the index of the bone with the given name in our list.
	// Returns INDEX_NONE if not found.
	IKINEMACORE_API int32 FindBoneIndex(const FName& boneName) const;

	// Gets the index of the task driving the bone referenced by boneIndex.
	// Returns INDEX_NONE if boneIndex is invalid or if bone is not being driven.
	IKINEMACORE_API int32 GetTaskIndexFromBone(int32 boneIndex) const;

	// Gets the index of the bone being driven by the task referenced by taskIndex.
	// Returns INDEX_NONE if taskIndex is invalid.
	IKINEMACORE_API int32 GetBoneIndexFromTask(int32 taskIndex) const;
};




USTRUCT(BlueprintType)
struct IKINEMACORE_API FIKinemaSolverTask
{
	GENERATED_USTRUCT_BODY()
	
	/*
		FTransform representing the task target in solver space, or the offset from the animation target depending on the value of AsOffset.
	*/
	UPROPERTY(BlueprintReadWrite, Category=Links)
	FTransform Target;

	/*
		Alpha factor for the linear interpolation between animation target and Target.
	*/
	UPROPERTY(BlueprintReadWrite, Category = Links)
	float Alpha;

	UPROPERTY(BlueprintReadWrite, Category = Links)
	TEnumAsByte<EIKinemaTargetType::Type> TargetType;

	/*
		The provided target transform is in component space
	*/
	UPROPERTY(BlueprintReadWrite, Category = Links)
	bool InComponentSpace;

	UPROPERTY(BlueprintReadWrite, Category=Links)
	bool EnableTranslation;
	UPROPERTY(BlueprintReadWrite, Category=Links)
	bool EnableOrientation;
	UPROPERTY(BlueprintReadWrite, Category=Links)
	bool DebugDraw;
	UPROPERTY(BlueprintReadWrite, Category=Links)
	float DebugDrawScale;

	FQuat PrevDeltaQ;
#if IKINEMA_WITH_SE
	FQuat MidPoint;
	FTransform PrevTarget;
	float DeltaStep;
	bool LookingBack;
#endif
	FIKinemaSolverTask();
};


USTRUCT(BlueprintType)
struct IKINEMACORE_API FIKinemaSolverLookAtTask: public FIKinemaSolverTask
{
	GENERATED_USTRUCT_BODY()

	/*
		FVector representing the task target in component space.
	*/
	UPROPERTY(BlueprintReadWrite, Category = Links)
	FVector LookAtTarget;

	/*
		FVector representing the LookAt Axis, in bone local space. If nothing is specified, the value exported in the rig will be used
	*/
	UPROPERTY(BlueprintReadWrite, Category = Links)
	FVector LookAtAxis;

	/*
		Position target in component space
	*/
	UPROPERTY(BlueprintReadWrite, Category = Links)
	FVector PositionTarget;


	UPROPERTY(BlueprintReadWrite, Category = Links)
	bool ReduceWeight;

	bool isLookAt;

	FIKinemaSolverLookAtTask();
};

USTRUCT(BlueprintType)
struct IKINEMACORE_API FIKinemaCOMTask
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Links)
	FVector Target;

	UPROPERTY(BlueprintReadWrite, Category = Links)
	bool Enable;

	UPROPERTY(BlueprintReadWrite, Category = Links)
	bool InComponentSpace;

	UPROPERTY(BlueprintReadWrite, Category = Links)
	bool DebugDraw;

	UPROPERTY(BlueprintReadWrite, Category = Links)
	float DebugDrawScale;

	FIKinemaCOMTask();
};


USTRUCT(BlueprintType)
struct IKINEMACORE_API FIKinemaTaskProperties
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool PositionDofX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool PositionDofY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool PositionDofZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	int32 PositionDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FVector PositionWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FVector PositionPrecision;

	//orientation

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, DisplayName = "Rotation DoF X")
	bool RotateDofX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, DisplayName = "Rotation DoF Y")
	bool RotateDofY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, DisplayName = "Rotation DoF Z")
	bool RotateDofZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	int32 RotateDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FVector RotateWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FVector RotatePrecision;

	FIKinemaTaskProperties();
};

USTRUCT(BlueprintType)
struct IKINEMACORE_API FIKinemaSegmentProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool	DofX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool	DofY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool	DofZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool	EnforceLimits;

	// One weight value for each bone axis.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FVector	Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool	EnableLimits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	float	LimitsGain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	bool	EnableRetargeting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	float	RetargetingGain;

	FIKinemaSegmentProperties();
};

USTRUCT(BlueprintType)
struct IKINEMACORE_API FIKinemaCOMTaskProperties
{
	GENERATED_USTRUCT_BODY()
	
	/*
	Enable or disable x-axis degree of freedom for driving the CoM
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, DisplayName = "CoM DoF X")
	bool DofX;

	/*
	Enable or disable y-axis degree of freedom for driving the CoM
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, DisplayName = "CoM DoF Y")
	bool DofY;
	
	/*
	Enable or disable z-axis degree of freedom for driving the CoM
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, DisplayName = "CoM DoF Z")
	bool DofZ;

	/*
	Importance Relative To Other Tasks.  
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FVector Weight;

	/* 
	Recommended value: Set between 2-4.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FVector Precision;

	FIKinemaCOMTaskProperties();
};


USTRUCT()
struct IKINEMACORE_API FIKinemaTaskOverride
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category=Links)
	FName	TaskName;

	UPROPERTY(EditAnywhere, Category=Links)
	bool	ShowAsPin;
};

USTRUCT()
struct IKINEMACORE_API FIKinemaSegmentOverride
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category=Links)
	FName	BoneName;

	UPROPERTY(EditAnywhere, Category=Links)
	bool	ShowAsPin;
};

USTRUCT()
struct IKINEMACORE_API FIKinemaCOMTaskOverride
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Links)
	FName	Name;

	UPROPERTY(EditAnywhere, Category = Links)
	bool	ShowAsPin;

};


UCLASS(hidecategories=Object, MinimalAPI, BlueprintType)
class UIKinemaRig : public UObject
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITORONLY_DATA
	// File containing a text description of this rig.
	// Not used from in-game runtime.
	UPROPERTY()
	FString ImportPath;
#endif //WITH_EDITORONLY_DATA
	UPROPERTY()
	int32	UpdateVersion;
	// The solver definition.
	UPROPERTY(EditAnywhere, Category = IKDefinition, meta = (ShowOnlyInnerProperties))
	FIKinemaSolverDef SolverDef;

	// Called just before re-importing properties from text.
	IKINEMACORE_API void PreReimport();

	// To do post-processing on loaded properties.
	virtual void PostLoad() override;

	// Called from the above, and from import.
	IKINEMACORE_API void PostLoadOrImport();

	
	//SetMaxIteration must be visible to other functions.
	IKINEMACORE_API void SetMaxIteration(int Iter);

	// Create an IKinema solver instance using this rig.
	void CreateSolver(class FIKinemaSolverInstance& solverInstance) const;

	void SolveAndUpdatePose(class FIKinemaSolverInstance& solverInstance, FPoseContext& ue4PoseInAndOut);

	void ClearDefinition();

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& PropertyChangedEvent );

	virtual void PreSave(const class ITargetPlatform* TargetPlatform);

	IKINEMACORE_API bool CreateRigFromSkeleton();
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skeleton)
	USkeleton* Skeleton;

	UPROPERTY()
	bool bIsVRRig;

private:
	int MaxIterations = 30;
	// Transfer an IKinema pose to UE4.
	void IKinemaToUE4Pose(class FIKinemaSolverInstance& solverInstance, FPoseContext& ue4Pose) const;
};

// Represents a binding of an IKinemaRig to a specific skeleton.
// Resolves UE4 bone indices and stores them.
class IKINEMACORE_API FIKinemaRigToSkeletonBinding
{
public:

	// Default constructor.
	FIKinemaRigToSkeletonBinding();

	// Bind the given IKinemaRig to the given skeleton and store the result.
	// Since the member properties are not stored on file, this should be called
	// from runtime each time, to set up the members.
	bool BindToSkeleton(UIKinemaRig* ikinemaRig, USkeleton* skeleton, USkeletalMeshComponent* component);

	// Configure the given solver using our cached data.
	void ConfigureSolver(FIK::IKSolver& solver) const;

	// Access the UE4 bone index given the bone def index.
	int32 GetUE4BoneIndex(int32 boneDefIndex) const;

	//int32 GetRootBoneIndex() const;

	// Access the IKinema rig.
	UIKinemaRig* GetRig() const;

	const USkeleton* GetSkeleton() const;

	const USkeletalMeshComponent* GetSkeletalMeshComponent() const;

	void ClearImportBones();

	bool IsValid() const;

private:

	// Remember the rig.
	UIKinemaRig* mRig;

	USkeleton* mSkeleton;

	USkeletalMeshComponent* mComponent;

	// Array of bones (IKinema segments) to directly import into the solver.
	TArray<FIK::ImportBone> ImportBones;

	// Cache the UE4 bone indices corresponding to IKinema segments.
	TArray<int32> UE4BoneIndices;
	//int32 RootBoneIndex; 
};

// This represents a task instance on a segment/joint/bone.
struct FIKinemaJointTaskInstance
{
	// Either of these could be null.
	FIK::IKPositionTask* mPositionTask;
	FIK::IKOrientationTask* mOrientationTask;

	// Default constructor.
	FIKinemaJointTaskInstance();

	// Utility methods to configure the tasks.

	void SetPositionWeight(const FVector& weight);
	void SetOrientationWeight(const FVector& weight);
	void SetPositionTarget(const FVector& positionTarget);
	void SetOrientationTarget(const FQuat& orientationTarget);
	void SetPositionEnabled(bool state);
	void SetOrientationEnabled(bool state);
	void ApplyPositionProperties(const FIKinemaTaskProperties& properties);
	void ApplyOrientationProperties(const FIKinemaTaskProperties& properties);
};

// This represents a COM task instance.
struct FIKinemaCOMTaskInstance
{
	// Either of these could be null.
	FIK::IKBalanceTask* mTask;

	// Default constructor.
	FIKinemaCOMTaskInstance();

	// Utility methods to configure the tasks.
	void SetWeight(const FVector& weight);
	void SetTarget(const FVector& positionTarget);
	void SetEnabled(bool state);
	void ApplyProperties(const FIKinemaCOMTaskProperties& properties);
};


// This represents an instance of an IKinema solver
// along with the tasks on it.
class IKINEMACORE_API FIKinemaSolverInstance
{
private:
	unsigned int InstID;
	// Binding to a skeleton.
	const FIKinemaRigToSkeletonBinding* mSkeletonBinding;

	// The array of tasks that were created on joints/segments.
	TArray<struct FIKinemaJointTaskInstance> mJointTasks;

	//The COM task wrapper
	FIKinemaCOMTaskInstance mCoMTask;

	// The IKinema solver.
	FIK::IKSolver* mIKSolver;

	FTransform mSolverToWorldSpace;

public:

	// Default constructor.
	FIKinemaSolverInstance();

	// Destructor.
	~FIKinemaSolverInstance();

	void Dump(const FString& Folder) const;

	// Create using the given skeleton binding.
	void Create(const FIKinemaRigToSkeletonBinding& skeletonBinding);

	// Destroy this solver instance.
	void Destroy();

	bool UpdateAndSolve(
		TArray<FIKinemaSolverTask>& tasks,
		const TArray<FIKinemaTaskProperties>& taskProperties,
		const TArray<FIKinemaTaskOverride>& taskOverride,
		const TArray<FIKinemaSegmentProperties>& segProperties,
		const TArray<FIKinemaSegmentOverride>& segOverride,
		/*CoM Task*/ const FIKinemaCOMTask& comTask,
		/*CoM Task Propertires*/ const FIKinemaCOMTaskProperties& comProperties,
		/*CoM Override*/ const FIKinemaCOMTaskOverride& comOverride,
		FPoseContext& Output);

	// Access the skeleton binding.
	const FIKinemaRigToSkeletonBinding* GetSkeletonBinding() const;
	
private:

	bool UpdateTaskInstances(const TArray<FIKinemaSolverTask>& tasks, const TArray<FIKinemaTaskProperties>& taskProperties, const TArray<FIKinemaTaskOverride>& taskOverride);
	bool UpdateCoM(const FIKinemaCOMTask& comTask, const FIKinemaCOMTaskProperties&  comProperties, const FIKinemaCOMTaskOverride& comOverride);
	friend class UIKinemaRig;
	friend struct FIKinemaSolverDef;
};
