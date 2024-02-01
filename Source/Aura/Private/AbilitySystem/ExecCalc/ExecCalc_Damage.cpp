// Copyright Lucas Rossi


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ParryChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			Armor,
			Target,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			ParryChance,
			Target,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			CriticalRate,
			Source,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			CriticalDamage,
			Source,
			false
		);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ParryChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = SourceASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	// Capture ParryChance on Target and determine if there was a successful Parry
	// If Parry, negate damage

	float TargetParryChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().ParryChanceDef,
		EvaluationParams,
		TargetParryChance
	);
	TargetParryChance = FMath::Max<float>(TargetParryChance, 0.f);
	const bool bParried = FMath::RandRange(1, 100) <= TargetParryChance;

	if (bParried)
	{
		Damage = 0.f;
	}
	else
	{
		float SourceCriticalRate = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			DamageStatics().CriticalRateDef,
			EvaluationParams,
			SourceCriticalRate
		);
		SourceCriticalRate = FMath::Max<float>(SourceCriticalRate, 0.f);
		const bool bCriticalHit = FMath::RandRange(1, 100) <= SourceCriticalRate;

		if (bCriticalHit)
		{
			float SourceCriticalDamage = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
				DamageStatics().CriticalDamageDef,
				EvaluationParams,
				SourceCriticalDamage
			);
			SourceCriticalDamage = FMath::Max<float>(SourceCriticalDamage, 150.f);

			Damage *= SourceCriticalDamage / 100.f;
		}
		
		
		float TargetArmor = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			DamageStatics().ArmorDef,
			EvaluationParams,
			TargetArmor
		);

		Damage *= (100 - TargetArmor) / 100.f;
	}

	const FGameplayModifierEvaluatedData EvaluatedData(
		UAuraAttributeSet::GetIncomingDamageAttribute(),
		EGameplayModOp::Additive,
		Damage
	);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
