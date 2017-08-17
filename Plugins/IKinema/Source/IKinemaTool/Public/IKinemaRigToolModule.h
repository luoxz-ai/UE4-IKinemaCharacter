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

#ifndef __IKinemaRigToolModule_h__
#define __IKinemaRigToolModule_h__

//#include "UnrealEd.h"
#include "ModuleInterface.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkit.h"
#include "IIKinemaRigTool.h"
#include "IKinemaRig.h"

extern const FName IKinemaRigToolAppIdentifier;

DECLARE_LOG_CATEGORY_EXTERN(LogIKinemaRigTool, Log, All);


/*-----------------------------------------------------------------------------
   IIKinemaRigToolModule
-----------------------------------------------------------------------------*/

class IIKinemaRigToolModule : public IModuleInterface,
	public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:

	virtual bool LicenseCheckPoint() { return true; };

	virtual bool isLicenseValid() { return true; };
	virtual bool DontAsk() { return false; };
	/** Creates a new IKinema RigTool instance */
	virtual TSharedRef<IIKinemaRigTool> CreateIKinemaRigTool(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UIKinemaRig* IKinemaRig) = 0;

};

#endif // __IKinemaRigToolModule_h__


