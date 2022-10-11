#include "P_Ball.h"
#include "Camera/CameraActor.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"

AP_Ball::AP_Ball()
{
	PrimaryActorTick.bCanEverTick = true;

	//Add Components
	PlayerStopWatch = CreateDefaultSubobject<UAC_StopWatch>(TEXT("StopWatch"));
}

void AP_Ball::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	PlayerController = UGameplayStatics::GetPlayerController(this,PlayerIndex);
	if (PlayerController != nullptr)
	{
		CameraComponent = PlayerController->GetViewTarget()->FindComponentByClass<UCameraComponent>();
	}
}

void AP_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddGravityZ();
}

void AP_Ball::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Accelerate"),this,&AP_Ball::HandleAccelerateInput);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"),this,&AP_Ball::HandleTurnRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AP_Ball::HandleJumpAction);
}

void AP_Ball::HandleAccelerateInput(float Value)
{
	if (CameraComponent == nullptr)
		return;
	
	float DriveForwardInput = Value;
	FVector Dir = CameraComponent->GetRightVector() * DriveForwardInput;

	if (MeshComponent != nullptr)
	{
		// MeshComponent->AddForce(Dir * Force * MeshComponent->GetMass() * GetWorld()->DeltaTimeSeconds, EName::None, true);
		MeshComponent->AddAngularImpulseInRadians(Dir * RollForce * GetWorld()->DeltaTimeSeconds, EName::None, false);
	}
	
	//FVector Dirr = FVector(0,DrivingSteerInput,0);
	//MeshComponent->AddForce(Force * Dirr * GetWorld()->DeltaTimeSeconds);
	// 
}

void AP_Ball::HandleTurnRight(float Value)
{
	if (CameraComponent == nullptr)
		return;
	
	float DrivingSteerInput = Value;
	FVector RollDir = CameraComponent->GetForwardVector() * DrivingSteerInput;
	FVector ForceDir = CameraComponent->GetRightVector() * DrivingSteerInput;
	
	if (MeshComponent != nullptr)
	{
		MeshComponent->AddAngularImpulseInRadians(RollDir * RollForce * GetWorld()->DeltaTimeSeconds, EName::None, false);
		MeshComponent->AddForce(ForceDir * PushForce * MeshComponent->GetMass() * GetWorld()->DeltaTimeSeconds, EName::None, true);
	}
}

void AP_Ball::HandleJumpAction()
{
	if (TryFlip())
	{
		GravityZ *= -1;
		TraceDirection *= -1;
		ReverseAngularVelocity();
	}
}

bool AP_Ball::TryFlip()
{
	FVector Start = MeshComponent->GetComponentLocation();
	FVector End = Start + TraceDirection * TraceLength;
	float Radius = 100;
	
	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore;
	
	//Ground check
	bool Trace = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, Radius,  TraceChannel, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true,  FLinearColor::Red, FLinearColor::Green, 2.0f);
	return Trace;
}

void AP_Ball::AddGravityZ()
{
	if (MeshComponent == nullptr)
		return;

	FVector Gravity = MeshComponent->GetMass() * FVector::DownVector * GravityZ * GetWorld()->DeltaTimeSeconds;
	MeshComponent->AddForce(Gravity);
}

void AP_Ball::ReverseAngularVelocity()
{
	if (MeshComponent == nullptr)
		return;
		FVector AngularVelocity = MeshComponent->GetPhysicsAngularVelocityInRadians();
	MeshComponent->SetPhysicsAngularVelocityInRadians(AngularVelocity * -1);
}
