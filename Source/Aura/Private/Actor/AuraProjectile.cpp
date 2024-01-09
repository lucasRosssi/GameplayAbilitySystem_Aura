// Copyright Lucas Rossi


#include "Actor/AuraProjectile.h"

// Sets default values
AAuraProjectile::AAuraProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuraProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

