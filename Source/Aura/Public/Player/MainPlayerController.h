// Copyright Lucas Rossi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "MainPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ITargetInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class AURA_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> MainContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	ITargetInterface* LastActor;
	ITargetInterface* ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	
	UAuraAbilitySystemComponent* GetASC();
};
