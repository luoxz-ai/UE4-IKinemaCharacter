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

/////////////////////////////////////////////////////
// TNewAssetAction
// Utility Action to add an asset to the graph
// This might be useful for other modules, so
// it's here in the Public folder.
//
#include "AssetRegistryModule.h"
#include "ARFilter.h"

template <class AssetType, class NodeType>
struct TNewAssetAction : public FEdGraphSchemaAction_K2NewNode
{
	TNewAssetAction(AssetType* asset, const FText& actionCategory)
	{
		check(asset != nullptr);

		NodeType* templateNode = NewObject<NodeType>();
		templateNode->Node.SetAsset(asset);
		NodeTemplate = templateNode;

		MenuDescriptionArray.Push(templateNode->GetNodeTitle(ENodeTitleType::ListView).ToString());

		MenuDescriptionArray.Push(templateNode->GetTooltipText().ToString());

		FullSearchCategoryArray.Push(actionCategory.ToString());

		// Grab extra keywords
		FullSearchKeywordsArray.Push(asset->ImportPath);
	}

	// Utility methods to use from the "GetMenuEntries" implementation of an AnimGraphNode.

	static void GetMenuEntriesAll(FGraphContextMenuBuilder& ContextMenuBuilder, FString const& actionCategory)
	{
		if ((ContextMenuBuilder.FromPin == NULL) || (UAnimationGraphSchema::IsPosePin(ContextMenuBuilder.FromPin->PinType) && (ContextMenuBuilder.FromPin->Direction == EGPD_Input)))
		{
			// Add an entry for each loaded asset.
			/*

			for (TObjectIterator<AssetType> assetIt; assetIt; ++assetIt)
			{
				AssetType* asset = *assetIt;
				
				 ContextMenuBuilder.AddAction( TSharedPtr< TNewAssetAction<AssetType, NodeType> >(new TNewAssetAction<AssetType, NodeType>(asset, actionCategory)));
				i++;
			}
			*/
			UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(ContextMenuBuilder.CurrentGraph);
			if (UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(Blueprint))
			{
				FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
				// define a filter to help in pulling IKinemaRig asset data from the registry
				FARFilter Filter;
				Filter.ClassNames.Add(AssetType::StaticClass()->GetFName());
				Filter.bRecursiveClasses = true;
				// Find matching assets and add an entry for each one
				TArray<FAssetData> RigList;
				AssetRegistryModule.Get().GetAssets(Filter, /*out*/RigList);

				for (auto AssetIt = RigList.CreateConstIterator(); AssetIt; ++AssetIt)
				{
					const FAssetData& Asset = *AssetIt;

					AssetType* rig = Cast<AssetType>(Asset.GetAsset());
					if (rig->Skeleton == nullptr || rig->Skeleton == AnimBlueprint->TargetSkeleton)

					{
						ContextMenuBuilder.AddAction(TSharedPtr< TNewAssetAction<AssetType, NodeType> >(new TNewAssetAction<AssetType, NodeType>(rig, FText::FromString(actionCategory))));
					}
					
				}

			}


		}
	}
};
