// Fill out your copyright notice in the Description page of Project Settings.


#include "TierOverflowLib_BPNodes.h"
#include "FGGamePhaseManager.h"
#include "FGSchematicManager.h"
#include "Net/UnrealNetwork.h"

#include "FGGamePhase.h"

bool UTierOverflowLib_BPNodes::ApplyPhase(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, UFGGamePhase* targetPhase, bool force = false) {
	if (!force && phaseManager->GetGamePhase() < EGamePhase::EGP_Victory)
		return false;

	if (!targetPhase)
		return false;

	FProperty* MaxAllowedTechTierProperty = AFGSchematicManager::StaticClass()->FindPropertyByName(TEXT("mMaxAllowedTechTier"));
	if (!MaxAllowedTechTierProperty)
		return false;

	void* PropertyAddress = MaxAllowedTechTierProperty->ContainerPtrToValuePtr<void>(schematicManager);
	if (!PropertyAddress)
		return false;

	MaxAllowedTechTierProperty->CopyCompleteValue(PropertyAddress, &targetPhase->mLastTierOfPhase);

	return IsValid(phaseManager) ? phaseManager->UpdateCurrentGamePhase(targetPhase) : false;
}

bool UTierOverflowLib_BPNodes::ApplyPhaseSimple(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, FString phaseName, int32 maxTierNumber, bool force = false) {
	if (!force && phaseManager->GetGamePhase() < EGamePhase::EGP_Victory)
		return false;

	FProperty* MaxAllowedTechTierProperty = AFGSchematicManager::StaticClass()->FindPropertyByName(TEXT("mMaxAllowedTechTier"));
	if (!MaxAllowedTechTierProperty)
		return false;

	void* PropertyAddress = MaxAllowedTechTierProperty->ContainerPtrToValuePtr<void>(schematicManager);
	if (!PropertyAddress)
		return false;

	MaxAllowedTechTierProperty->CopyCompleteValue(PropertyAddress, &maxTierNumber);

	UFGGamePhase* newPhase = NewObject<UFGGamePhase>();

	if (newPhase)
	{
		newPhase->mDisplayName = FText::FromString(!phaseName.IsEmpty() ? phaseName : FString(maxTierNumber + "-tier"));
		newPhase->mLastTierOfPhase = maxTierNumber;
		newPhase->mPriority = .0f;
		newPhase->mCosts = TArray<FItemAmount>();
		newPhase->mGamePhase = EGamePhase::EGP_NA;
		newPhase->mPhaseTag = FGameplayTag();
	}

	return IsValid(newPhase) ? phaseManager->UpdateCurrentGamePhase(newPhase) : false;
}

bool UTierOverflowLib_BPNodes::ApplyMaxTier(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, int32 maxTierNumber, bool force) {
	if (force || maxTierNumber > schematicManager->GetMaxAllowedTechTier()) {
		FProperty* MaxAllowedTechTierProperty = AFGSchematicManager::StaticClass()->FindPropertyByName(TEXT("mMaxAllowedTechTier"));
		if (!MaxAllowedTechTierProperty)
			return false;

		void* PropertyAddress = MaxAllowedTechTierProperty->ContainerPtrToValuePtr<void>(schematicManager);
		if (!PropertyAddress)
			return false;

		MaxAllowedTechTierProperty->CopyCompleteValue(PropertyAddress, &maxTierNumber);
	}

	if (force || maxTierNumber > phaseManager->GetCurrentGamePhase()->mLastTierOfPhase) {
		phaseManager->GetCurrentGamePhase()->mLastTierOfPhase = maxTierNumber;
	}

	return (phaseManager->GetCurrentGamePhase()->mLastTierOfPhase >= maxTierNumber && schematicManager->GetMaxAllowedTechTier() >= maxTierNumber);
}

bool UTierOverflowLib_BPNodes::ApplyVanillaPhaseFromIndex(AFGGamePhaseManager* phaseManager, int32 index) {
	return IsValid(phaseManager) ? phaseManager->SetGamePhaseFromGamePhaseIndex(index) : false;
}

void UTierOverflowLib_BPNodes::ApplyNextVanillaPhase(AFGGamePhaseManager* phaseManager) {
	if(!IsValid(phaseManager))
		return;

	phaseManager->GoToNextGamePhase();
}

void UTierOverflowLib_BPNodes::UnlockAllVanillaPhases(AFGGamePhaseManager* phaseManager) {
	if (!IsValid(phaseManager))
		return;

	phaseManager->UnlockAllGamePhases();
}

bool UTierOverflowLib_BPNodes::ForceApplySchematic(AFGSchematicManager* schematicManager, TSubclassOf<  UFGSchematic > newActiveSchematic) {
	UFGSchematic* SchematicCDO = newActiveSchematic->GetDefaultObject<UFGSchematic>();
	if (SchematicCDO)
	{
		FProperty* TechTierProperty = UFGSchematic::StaticClass()->FindPropertyByName(TEXT("mTechTier"));
		if (TechTierProperty)
		{
			int32 OriginalTechTier = 0;
			void* PropertyAddress = TechTierProperty->ContainerPtrToValuePtr<void>(SchematicCDO);
			TechTierProperty->CopyCompleteValue(&OriginalTechTier, PropertyAddress);

			int32 NewTechTier = 0;
			TechTierProperty->CopyCompleteValue(PropertyAddress, &NewTechTier);

			bool result = schematicManager->SetActiveSchematic(newActiveSchematic);

			TechTierProperty->CopyCompleteValue(PropertyAddress, &OriginalTechTier);

			return result;
		}
	}
	return false;
}