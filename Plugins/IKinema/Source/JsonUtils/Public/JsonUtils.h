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

class JSONUTILS_API FJsonUtils
{
public:

	// Import a UObject from a json string.
	static bool ImportObjectFromJsonString( UObject* Object, const FString& JsonString, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );
	// Import a UObject from a json.
	static bool ImportObjectFromJson( UObject* Object, const TSharedPtr<class FJsonObject>& JSONObject, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );
	static bool ImportDataFromJsonString( uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, const FString& JsonString, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );
	// Create a UObject from a json string.
	static bool CreateObjectFromJsonString( UObject*& Object, UObject* Parent, const FString& JsonString, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );

	// Export a UObject to a json string
	static bool ExportObjectToJsonString( const UObject* Object, FString& JSONString, bool bExportClassName, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );
	static bool ExportJsonObjectToString( TSharedPtr<FJsonObject>& JObj, FString& JSONString );

	// Export a UObject to a json
	static bool ExportObjectToJson( const UObject* Object, TSharedPtr<class FJsonValue>& JObjValue, bool bExportClassName, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );
	static bool ExportDataToJsonString( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, FString& JSONString, bool bExportClassName, int32 PortFlags=PPF_ExportsNotFullyQualified|PPF_Copy );
};
