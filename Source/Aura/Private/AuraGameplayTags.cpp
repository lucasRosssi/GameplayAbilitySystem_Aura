// Copyright Lucas Rossi


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * PRIMARY ATTRIBUTES
	 */ 
	
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases melee damage and maximum health")
		);
	
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magic damage and maximum mana")
		);

	GameplayTags.Attributes_Primary_Toughness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Toughness"),
		FString("Increases armor and maximum stamina")
		);

	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Agility"),
			FString("Increases movement speed and stamina efficiency")
			);

	GameplayTags.Attributes_Primary_Finesse = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Finesse"),
		FString("Increases action speed and critical rate")
		);

	/*
	 * SECONDARY ATTRIBUTES
	 */

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of health")
		);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of mana")
		);

	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"),
		FString("Maximum amount of stamina")
		);
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken")
		);

	GameplayTags.Attributes_Secondary_ActionSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ActionSpeed"),
		FString("Attack, cast and skill speed")
		);

	GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(
		FName("Attributes.Secondary.MovementSpeed"),
		FString("Running speed and dodge range")
		);

	GameplayTags.Attributes_Secondary_CriticalRate = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalRate"),
		FString("Chance to do a critical hit")
		);

	GameplayTags.Attributes_Secondary_CriticalDamage = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalDamage"),
		FString("Percentage of damage a critical hit deals")
		);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of health recovered over time")
		);
	
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of mana recovered over time")
		);

	GameplayTags.Attributes_Secondary_StaminaRegeneration = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(
		FName("Attributes.Secondary.StaminaRegeneration"),
		FString("Amount of stamina recovered over time")
		);

	GameplayTags.Attributes_Secondary_StaminaEfficiency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.StaminaEfficiency"),
		FString("Stamina cost reduction")
		);

	/*
	 * INPUT TAGS
	 */

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);
}
