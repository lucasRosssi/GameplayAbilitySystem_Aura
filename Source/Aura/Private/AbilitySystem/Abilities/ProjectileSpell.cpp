// Copyright Lucas Rossi


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"

void UProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor);
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetProjectileSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AActor* OwningActor = GetOwningActorFromActorInfo();
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			OwningActor,
			Cast<APawn>(AvatarActor),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		const UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
		
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
			DamageEffectClass,
			GetAbilityLevel(),
			SourceASC->MakeEffectContext()
		);

		
		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		
		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			SpecHandle,
			GameplayTags.Damage,
			ScaledDamage
		);

		
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
