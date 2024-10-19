// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TierOverflowLib_BPNodes.generated.h"

/**
 * 
 */
UCLASS()
class TIEROVERFLOWLIB_API UTierOverflowLib_BPNodes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Phase Management")
	static bool ApplyPhase(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, UFGGamePhase* targetPhase, bool force);

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Phase Management")
	static bool ApplyPhaseSimple(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, FString phaseName, int32 maxTierNumber, bool force);

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Tier Management")
	static bool ApplyMaxTier(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, int32 maxTierNumber, bool force);

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Phase Management")
	static bool ApplyVanillaPhaseFromIndex(AFGGamePhaseManager* phaseManager, int32 index);

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Phase Management")
	static void ApplyNextVanillaPhase(AFGGamePhaseManager* phaseManager);

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Phase Management")
	static void UnlockAllVanillaPhases(AFGGamePhaseManager* phaseManager);

	UFUNCTION(BlueprintCallable, Category = "TierOverflowLib Schematic Management")
	static bool ForceApplySchematic(AFGSchematicManager* schematicManager, TSubclassOf<  UFGSchematic > newActiveSchematic);
};
