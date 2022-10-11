#include "BallMovment.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnitConversion.h"
#include "Math/UnrealMathUtility.h"


ABallMovment::ABallMovment()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}
void ABallMovment::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallMovment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Velocity += GetActorForwardVector() * CurrentSpeed * DeltaTime;

	FVector RollingVelocity = Velocity.ProjectOnTo(GetActorForwardVector());
	FVector GripVelocity = Velocity - RollingVelocity;
	RollingVelocity -= RollingVelocity * RollFriction * DeltaTime;
	GripVelocity -= GripVelocity * GripFriction * DeltaTime; 

	Velocity = GripVelocity + RollingVelocity;
	
	float Speed = FVector::DotProduct(Velocity, GetActorForwardVector());

	
	AddActorWorldOffset(Velocity * DeltaTime);
	AddControllerYawInput(DrivingSteerInput * SpeedToRotationFactor * Speed * DeltaTime);

}

void ABallMovment::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Accelerate"),this,&ABallMovment::HandleAccelerateInput);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"),this,&ABallMovment::HandleTurnRight);

}

void ABallMovment::HandleAccelerateInput(float Value)
{
	DriveForwardInput = Value;
	CurrentSpeed =  FMath::FInterpTo(CurrentSpeed, DriveForwardInput * MaxSpeed, GetWorld()->GetDeltaSeconds(), InterpSpeed);

	GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Blue,FString::Printf(TEXT("CurrentSpeed: %f"),CurrentSpeed));
	GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Blue,FString::Printf(TEXT("Accelerate: %f"),DriveForwardInput));
}

void ABallMovment::HandleTurnRight(float Value)
{
	DrivingSteerInput = Value;
	GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Blue,FString::Printf(TEXT("Accelerate: %f"),DrivingSteerInput));
}

