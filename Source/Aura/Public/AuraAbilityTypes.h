#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsCriticalHit() const { return bCriticalHit; }
	bool IsParried() const { return bParried; }

	void SetIsCriticalHit(bool bInCriticalHit) { bCriticalHit = bInCriticalHit; }
	void SetIsParry(bool bInParry) { bParried = bInParry; }
	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
protected:
	UPROPERTY()
	bool bParried = false;
	UPROPERTY()
	bool bCriticalHit = false;
};
