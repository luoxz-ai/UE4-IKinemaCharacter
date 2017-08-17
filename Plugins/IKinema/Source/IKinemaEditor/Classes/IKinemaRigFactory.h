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
//=============================================================================
// Factory for a definition of an IKinema solver.
// The factory creates the solver definition.
// The solver definition creates the solver.
//=============================================================================
#pragma once
#include "EditorReimportHandler.h"
#include "Factories/Factory.h"
#include "IKinemaRigFactory.generated.h"

UCLASS(hidecategories=Object)
class UIKinemaRigFactory : public UFactory, public FReimportHandler
{
	GENERATED_UCLASS_BODY()

	class USkeleton* TargetSkeleton;
	bool IsVR;
	// Begin UFactory Interface
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;
	
	// End UFactory Interface

	// Begin FReimportHandler interface
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;
	bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End FReimportHandler interface

private:

	// Read from a text buffer.
	bool ReadFromText(class UIKinemaRig* rig, const TCHAR* type, const TCHAR*& buffer, const TCHAR* bufferEnd, FFeedbackContext* warn);
};
