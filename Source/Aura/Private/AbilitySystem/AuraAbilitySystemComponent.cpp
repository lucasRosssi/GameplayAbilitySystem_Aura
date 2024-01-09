// Copyright Lucas Rossi


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(
		this,
		&UAuraAbilitySystemComponent::EffectApplied
	);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities
)
{
	for (const auto AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const auto* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		
		AbilitySpecInputPressed(AbilitySpec);
		
		if (AbilitySpec.IsActive()) continue;
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		
		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::EffectApplied(
	UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle ActiveEffectHandle
)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}

