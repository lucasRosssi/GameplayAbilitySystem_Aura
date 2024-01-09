// Copyright Lucas Rossi


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "Kismet/KismetSystemLibrary.h"

void UProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKismetSystemLibrary::PrintString(
		this,
		FString("ActivateAbility (C++)"),
		true,
		true,
		FLinearColor::Green,
		3
	);
}
