
#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "A_Camera.generated.h"

class UCameraComponent;
UCLASS()
class GP4T4_API AA_Camera : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AA_Camera();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category= "Camera Follow|Advanced")
	float FollowSpeed = 20.f;

	UPROPERTY(EditAnywhere, Category= "Camera Follow|Advanced")
	float RotationSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category= "Camera Follow|Advanced")
	FVector DistanceBetween = FVector(-5,0,10);
	
	UPROPERTY(EditAnywhere, Category= "Camera Follow|Advanced")
	USplineComponent* Spline;
	
	UPROPERTY()
	APlayerController* PlayerController;
	// UPROPERTY()
	// UMeshComponent* PlayerMesh;

	UFUNCTION()
	void LerpToLocationAndRotation(FVector DesiredLocation, FRotator DesiredRotation, float DeltaTime);
	
};

