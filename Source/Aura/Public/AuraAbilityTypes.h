#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsCriticalHit() const { return bCriticalHit; }
	bool IsParry() const { return bParry; }

	void SetIsCriticalHit(bool bInCriticalHit) { bCriticalHit = bInCriticalHit; }
	void SetIsParry(bool bInParry) { bParry = bInParry; }
	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
protected:
	UPROPERTY()
	bool bParry = false;
	UPROPERTY()
	bool bCriticalHit = false;
};
