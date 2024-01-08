// Copyright Lucas Rossi


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const auto& Action : AbilityInputActions)
	{
		if (Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT(
			"Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"
			), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
