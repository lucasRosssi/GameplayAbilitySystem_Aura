// Copyright Lucas Rossi


#include "AI/Services/BTService_FindNearestTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindNearestTarget::UBTService_FindNearestTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find Nearest Target";
}

void UBTService_FindNearestTarget::TickNode(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory,
	float DeltaSeconds
)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsOfClassWithTag(
		OwningPawn,
		ActorClass,
		TargetTag,
		ActorsWithTag
	);

	float ClosestDistance = 2000.f;
	AActor* ClosestActor = nullptr;
	for (const auto Actor : ActorsWithTag)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject(TargetToFollowSelector.SelectedKeyName, ClosestActor);
	BlackboardComponent->SetValueAsFloat(DistanceToTargetSelector.SelectedKeyName, ClosestDistance);
}
