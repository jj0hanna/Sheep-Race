#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "A_Camera3.generated.h"

class UCameraComponent;
UCLASS()
class GP4T4_API AA_Camera3 : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AA_Camera3();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* ActiveSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* PreviousSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* MasterSpline;
	
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* PlayerPrimitiveComponent;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | FollowSpeed")
	float FollowSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, Category= "Camera Settings | SpringArm")
	float DefaultArmLength = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category= "Camera Settings | SpringArm")
	float PlayerFlippedArmlength = 500.f;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | InterpSpeed")
	float InterpSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | RotationSpeed")
	float CameraSpringRotationSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | RotationSpeed")
	float CameraSpringRotationSpeedWhenFlipped = 5.f;

	UPROPERTY()
	float DefaultCameraRotationSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | RotationSpeed")
	float LookAtSpeed = 2.f;

	UPROPERTY()
	float NewFieldOfView;

	UPROPERTY()
	float CurrentFieldOfView;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float DefaultFieldOfView = 100;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float FieldOfViewTr1 = 50;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float FieldOfViewTr2 = 50;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float FieldOfViewTr3 = 50;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float FieldOfViewChangeSpeed;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float PlayerVelocityTr1 = 3800.f;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float PlayerVelocityTr2 = 4000.f;

	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	float PlayerVelocityTr3 = 5000.f;
	
	UPROPERTY(EditAnywhere, Category= "Camera Settings | Field Of View")
	bool bChangeFieldOfView = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Meta = (ExposeOnSpawn = true), Category="Camera Settings | Index")
	int PlayerInt = 0;

	UPROPERTY()
	FVector PlayerVelocity;

	UPROPERTY()
	bool bPlayerIsFlipped = false;

	UPROPERTY()
	FVector PlayerComponentLocation;

	UFUNCTION()
	void SetCameraLocationAndRotation();
	
	UFUNCTION()
	void SetCameraRotation();

	UFUNCTION()
	void LookAtPlayer() const;
	
	UFUNCTION(BlueprintCallable)
	void SmoothSplineChange();

	UFUNCTION(BlueprintCallable)
	void PlayerIsFlippedCameraChange(bool isFlipped);

	UFUNCTION(BlueprintCallable)
	void SetCameraStartLocation() const;

	UFUNCTION(BlueprintCallable)
	void ChangeFieldOfView(float DeltaTime);
};


