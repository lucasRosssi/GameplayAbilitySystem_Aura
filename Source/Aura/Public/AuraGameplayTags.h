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
protected:
 
private:
	static FAuraGameplayTags GameplayTags;
};
