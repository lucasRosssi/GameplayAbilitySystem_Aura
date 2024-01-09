// Copyright Lucas Rossi


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetCharacterLevel()
{
	return 0;
}

FVector ICombatInterface::GetProjectileSocketLocation()
{
	return FVector();
}
