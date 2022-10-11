// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpPickup.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GP4T4/AC_StopWatch.h"
#include "P_Ball.generated.h"

UCLASS()
class GP4T4_API AP_Ball : public APawn
{
	GENERATED_BODY()

public:
	
	AP_Ball();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void HandleAccelerateInput(float Value);
	UFUNCTION()
	void HandleTurnRight(float Value);
	UFUNCTION()
	void HandleJumpAction();

	UPROPERTY()
	int PlayerIndex = 0;
	UPROPERTY()
	FString PlayerName;
	
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	AActor* Camera;
	UPROPERTY()
	UCameraComponent* CameraComponent;
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;
	UPROPERTY()
	UAC_StopWatch* PlayerStopWatch;
	
	//Movement
	UPROPERTY(EditDefaultsOnly, Category= "Movement")
	float RollForce = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category= "Movement")
	float PushForce = 1000.f;
	
	//GroundCheck
	UPROPERTY(EditDefaultsOnly, Category= "Ground Check")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;
	UPROPERTY(EditDefaultsOnly, Category= "Ground Check")
	float TraceLength = 200.f;


	//Gravity
	UPROPERTY(EditDefaultsOnly, Category= "Gravity")
	float GravityZ = 50000.f;


	UFUNCTION()
	bool TryFlip();
	UFUNCTION()
	void AddGravityZ();
	UFUNCTION()
	void ReverseAngularVelocity();

	//Abilities
	UPROPERTY()
	TEnumAsByte<PowerUpType> AbilitySlot;

private:
	FVector TraceDirection = FVector::DownVector;
	bool bHasAbility = false;
	
};
