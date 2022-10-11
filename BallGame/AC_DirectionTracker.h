#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_DirectionTracker.generated.h"

UCLASS(Blueprintable)
class GP4T4_API UAC_DirectionTracker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_DirectionTracker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION()
	void AddCount();
	UFUNCTION()
	void ResetCount();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBadDirection();
	UFUNCTION(BlueprintImplementableEvent)
	void OnGoodDirection();
	
private:
	UPROPERTY()
	int MaxWrong = 2;
	UPROPERTY()
	int Count = 0;
	UPROPERTY()
	bool bDoCount = true;
};
