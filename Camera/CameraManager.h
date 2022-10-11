#pragma once

#include "CoreMinimal.h"
#include "A_Camera.h"
#include "A_Camera2.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"

UCLASS()
class GP4T4_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACameraManager();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AActor* Camera1;

	UPROPERTY(EditAnywhere)
	AActor* Camera2;

	UPROPERTY(EditAnywhere)
	AActor* Camera3;

	
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	UPROPERTY()
	float TimeToNextCameraChange;

	float SmoothblendTime = 0.75f;

	UFUNCTION(BlueprintCallable)
	void SetCameraOne();

	UFUNCTION(BlueprintCallable)
	void SetCameraTwo();

	UFUNCTION(BlueprintCallable)
	void SetCameraThree();

	UFUNCTION(BlueprintCallable)
	AActor* GetCamera();

};
