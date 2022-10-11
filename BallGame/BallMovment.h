

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BallMovment.generated.h"

UCLASS()
class GP4T4_API ABallMovment : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABallMovment();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HandleAccelerateInput(float Value);
	UFUNCTION()
	void HandleTurnRight(float Value);
	
	float DriveForwardInput = 0.f;
	float DrivingSteerInput = 0.f;

	UPROPERTY(BlueprintReadWrite)
	FVector Velocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite)
	float CurrentSpeed = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category= "CarMovement", BlueprintReadWrite)
	float MaxSpeed = 500.f;
	UPROPERTY(EditDefaultsOnly, Category= "CarMovement")
	float SpeedToRotationFactor = 0.008;
	UPROPERTY(EditDefaultsOnly, Category= "CarMovement")
	float RollFriction = 0.8f;// to apply forward roll friction to the "tires"
	UPROPERTY(EditDefaultsOnly, Category= "CarMovement", BlueprintReadWrite)
	float GripFriction = 3.8f;
	UPROPERTY(EditDefaultsOnly, Category= "CarMovement")
	float InterpSpeed = 1.f;// to apply "side grip friction" to the "tires"
	
	

};
