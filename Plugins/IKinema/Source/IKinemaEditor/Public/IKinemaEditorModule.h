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
#include "AllowWindowsPlatformTypes.h"
#include "IKinemaEditorModule.h"

DECLARE_LOG_CATEGORY_EXTERN(LogIKinemaEditor, Warning, All);

class FIKinemaEditorModule : public IModuleInterface
{
public:
	FIKinemaEditorModule();

	void StartupModule() override;
	void ShutdownModule() override;

	static bool LicenseCheckPoint();
	bool isLicenseValid() const;
	virtual TSharedPtr<FExtensibilityManager> GetIKinemaEditorMenuExtensibilityManager() { return IKinemaEditor_MenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetIKinemaEditorToolBarExtensibilityManager() { return IKinemaEditor_ToolBarExtensibilityManager; }

private:
	// Asset type actions for IKinema assets.  Cached here so that we can unregister it during shutdown.
	TSharedPtr< class FAssetTypeActions_IKinemaRig > mIKinemaRigAssetTypeActions;
	//TSharedPtr< class FAssetTypeActions_IKinemaTaskSkeleton > mIKinemaTaskSkeletonAssetTypeActions;
	//TSharedPtr< class FAssetTypeActions_IKinemaTaskAnim > mIKinemaTaskAnimAssetTypeActions;

	TSharedPtr<FExtensibilityManager> IKinemaEditor_MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> IKinemaEditor_ToolBarExtensibilityManager;

	bool isLicensed;

};
