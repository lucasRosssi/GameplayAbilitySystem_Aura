// Copyright Lucas Rossi


#include "AbilitySystem/ModMagCalc/MMC_MaxStamina.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxStamina::UMMC_MaxStamina()
{
	ToughnessDef.AttributeToCapture = UAuraAttributeSet::GetToughnessAttribute();
	ToughnessDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ToughnessDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ToughnessDef);
}

float UMMC_MaxStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	float Toughness = 0.f;
	GetCapturedAttributeMagnitude(ToughnessDef, Spec, EvaluationParams, Toughness);
	Toughness = FMath::Max(Toughness, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level = CombatInterface->GetCharacterLevel();

	return 20.f + 2.f * (Toughness - 10.f) + 4.f * (Level - 1);
}
