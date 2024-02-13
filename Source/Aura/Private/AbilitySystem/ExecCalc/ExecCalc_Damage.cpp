// Copyright Lucas Rossi


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ParryChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnergyResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
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
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			PhysicalResistance,
			Target,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			EnergyResistance,
			Target,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			FireResistance,
			Target,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			IceResistance,
			Target,
			false
		);
		DEFINE_ATTRIBUTE_CAPTUREDEF(
			UAuraAttributeSet,
			LightningResistance,
			Target,
			false
		);

		const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Special_ParryChance, ParryChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalRate, CriticalRateDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalDamage, CriticalDamageDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Energy, EnergyResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Ice, IceResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
		
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
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().EnergyResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().IceResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
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
	float Damage = 0.f;
	for (const auto& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		checkf(
			AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),
			TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"),
			*ResistanceTag.ToString()
		);
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = AuraDamageStatics()
			.TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag);
		
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			CaptureDef,
			EvaluationParams,
			Resistance
		);
		Resistance = FMath::Min(Resistance, 100.f);

		DamageTypeValue *= ( 100.f - Resistance ) / 100.f;
		
		Damage += DamageTypeValue;
	}

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

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsParried(EffectContextHandle, bParried);

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

		UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

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
