// Copyright Lucas Rossi


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetProjectileSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set the Projectile Rotation
		
		AActor* OwningActor = GetOwningActorFromActorInfo();
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			OwningActor,
			Cast<APawn>(OwningActor),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		//TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.

		Projectile->FinishSpawning(SpawnTransform);
	}

	
}
