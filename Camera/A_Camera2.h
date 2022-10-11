// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Camera2.generated.h"

class UCameraComponent;
UCLASS()
class GP4T4_API AA_Camera2 : public AActor
{
	GENERATED_BODY()
	
public:	

	AA_Camera2();

protected:
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category= "Camera Follow|Advanced")
	float FollowSpeed = 5.f;

	UPROPERTY()
	FVector DistanceBetween = FVector(5,0,10);
};
