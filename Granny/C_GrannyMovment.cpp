#include "C_GrannyMovment.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnitConversion.h"
#include "Math/UnrealMathUtility.h"

AC_GrannyMovment::AC_GrannyMovment()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void AC_GrannyMovment::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_GrannyMovment::Tick(float DeltaTime)
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

void AC_GrannyMovment::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Accelerate"),this,&AC_GrannyMovment::HandleAccelerateInput);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"),this,&AC_GrannyMovment::HandleTurnRight);

}

void AC_GrannyMovment::HandleAccelerateInput(float Value)
{
	DriveForwardInput = Value;
	CurrentSpeed =  FMath::FInterpTo(CurrentSpeed, DriveForwardInput * MaxSpeed, GetWorld()->GetDeltaSeconds(), InterpSpeed);

	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Blue,FString::Printf(TEXT("CurrentSpeed: %f"),CurrentSpeed));
	GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Blue,FString::Printf(TEXT("Accelerate: %f"),DriveForwardInput));
}

void AC_GrannyMovment::HandleTurnRight(float Value)
{
	DrivingSteerInput = Value;
}

