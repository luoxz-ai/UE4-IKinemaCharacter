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
#include "AnimGraphNode_Base.h"
#include "AnimNode_SaveBoneTransform.h"
#include "AnimGraphNode_SaveBoneTransform.generated.h"

UCLASS(MinimalAPI)
class UAnimGraphNode_SaveBoneTransform: public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	FAnimNode_SaveBoneTransform Node;

#if WITH_EDITOR
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	// End of UEdGraphNode interface
#endif
};
