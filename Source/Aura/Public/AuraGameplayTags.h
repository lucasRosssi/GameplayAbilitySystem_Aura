// Copyright Lucas Rossi

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
  static const FAuraGameplayTags& Get() { return GameplayTags; }
  static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Toughness;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Finesse;

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;
	
  FGameplayTag Attributes_Secondary_Armor;
  FGameplayTag Attributes_Secondary_ActionSpeed;
  FGameplayTag Attributes_Secondary_MovementSpeed;
  FGameplayTag Attributes_Secondary_CriticalRate;
  FGameplayTag Attributes_Secondary_CriticalDamage;
  FGameplayTag Attributes_Secondary_HealthRegeneration;
  FGameplayTag Attributes_Secondary_ManaRegeneration;
  FGameplayTag Attributes_Secondary_StaminaRegeneration;
  FGameplayTag Attributes_Secondary_StaminaEfficiency;

	FGameplayTag Attributes_Resistance_Physical;
	FGameplayTag Attributes_Resistance_Energy;
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Ice;
	FGameplayTag Attributes_Resistance_Lightning;

	FGameplayTag Attributes_Special_ParryChance;

	FGameplayTag Damage;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Energy;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Ice;
	FGameplayTag Damage_Lightning;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	
	FGameplayTag Effects_HitReact;

	FGameplayTag Abilities_HitReact;

private:
	static FAuraGameplayTags GameplayTags;
};
