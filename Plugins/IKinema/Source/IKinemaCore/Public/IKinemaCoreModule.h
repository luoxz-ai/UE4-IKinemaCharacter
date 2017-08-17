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
#include "ModuleInterface.h"
#include "TaskGraphInterfaces.h"

class FIKinemaCoreModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};
FGraphEventRef ExecOnGameThread(TFunction<void()> funcLambda);
const FString GetIKinemaLicense();