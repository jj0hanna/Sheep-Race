#include "A_Camera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AA_Camera::AA_Camera()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = Root;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);
	
	// Create a camera boom
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	////Camera attatch the camera to the boom
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//Camera->bUsePawnControlRotation = false;
}

void AA_Camera::BeginPlay()
{
	Super::BeginPlay();

	//** Get spline **
	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetViewTarget(this);
	
	// PlayerMesh = PlayerController->FindComponentByClass<UMeshComponent>();
	// PlayerMesh = UGameplayStatics::GetPlayerPawn(GetWorld(),0)->FindComponentByClass<UMeshComponent>();
	// UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetFocalLocation();
	FVector CameraPos = GetActorLocation();
	
	DistanceBetween = PlayerLocation - CameraPos;

}


void AA_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// use player location and direction instead somehow?
	
	FVector PlayerLocation = PlayerController->GetFocalLocation() + PlayerController->FindComponentByClass<UMeshComponent>()->GetComponentVelocity();
	FVector CameraLocation = GetActorLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation( CameraLocation, PlayerLocation);

	// FRotator CameraRotation = GetActorRotation();
	// FRotator CameraRot = FMath::RInterpTo(CameraRotation,TargetRotation,DeltaTime ,RotationSpeed);
	// CameraLocation = FMath::Lerp(CameraLocation,PlayerLocation - DistanceBetween,FollowSpeed * DeltaTime);
	// SetActorLocationAndRotation(CameraLocation,CameraRot);
	//CameraRot = FMath::Lerp(CameraPos,PlayerLocation - DistanceBetween,FollowSpeed * DeltaTime);
	
	LerpToLocationAndRotation(PlayerLocation, TargetRotation, DeltaTime);

	// if(GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Target Rotation: %f - %f - %f"), TargetRotation.Pitch, TargetRotation.Yaw, TargetRotation.Roll));
	// 	GEngine->AddOnScreenDebugMessage(-20, 1.f, FColor::Yellow, FString::Printf(TEXT("Actor Rotation: %f - %f - %f"), GetActorRotation().Pitch, GetActorRotation().Yaw,GetActorRotation().Roll));
	//
	// }
}

void AA_Camera::LerpToLocationAndRotation(FVector DesiredLocation, FRotator DesiredRotation, float DeltaTime)
{
	FVector Location = FMath::Lerp(GetActorLocation(),DesiredLocation - DistanceBetween,FollowSpeed * DeltaTime);
	FRotator Rotation = FMath::RInterpTo(GetActorRotation(),DesiredRotation, DeltaTime ,RotationSpeed);
	
	SetActorLocationAndRotation(Location,Rotation);
}
