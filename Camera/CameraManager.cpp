#include "CameraManager.h"

#include "A_Camera.h"
#include "A_Camera2.h"
#include "A_Camera3.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GP4T4/GP4T4.h"

ACameraManager::ACameraManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetFocalLocation();
	//Cam1
	FVector SpawnLoc = FVector(-1507,0,411);
	FRotator SpawnRot = FRotator(-10,0,0);
	//Cam2
	FVector SpawnLoc2 = FVector(1507,0,611);
	FRotator SpawnRot2 = FRotator(-20,180,0);
	//Cam3
	FVector SpawnLoc3 = FVector(-1507,0,-100);
	FRotator SpawnRot3 = FRotator(0,0,0);
	
	FActorSpawnParameters SpawnInfo;
	
	//SpawnLocation relative to the player
	SpawnLoc += PlayerLocation;
	SpawnLoc2 += PlayerLocation;
	SpawnLoc3 += PlayerLocation;

	//spawn the camera/actor, should be done in the gamemode?
	AActor* SpawnCamera1 = GetWorld()->SpawnActor<AA_Camera>(SpawnLoc,SpawnRot,SpawnInfo);
	AActor* SpawnCamera2 = GetWorld()->SpawnActor<AA_Camera2>(SpawnLoc2,SpawnRot2,SpawnInfo);
	AActor* SpawnCamera3 = GetWorld()->SpawnActor<AA_Camera3>(SpawnLoc3,SpawnRot3,SpawnInfo);

	Camera1 = SpawnCamera1;
	Camera2 = SpawnCamera2;
	Camera3 = SpawnCamera3;
	
	PlayerController = UGameplayStatics::GetPlayerController(this,0);
	
	if ((PlayerController->GetViewTarget() != Camera1) && (Camera1 != nullptr))
	{
		PlayerController->SetViewTarget(Camera1);
	}
}


void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChange = 2.0f;
	TimeToNextCameraChange -= DeltaTime;

	//if (TimeToNextCameraChange <= 0.0f)
	//{
	//	TimeToNextCameraChange += TimeBetweenCameraChange;
//
	//	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this,0);
	//	if ((PlayerController->GetViewTarget() != Camera1) && (Camera1 != nullptr))
	//	{
	//		PlayerController->SetViewTarget(Camera1);
	//	}
	//	else if((PlayerController->GetViewTarget() != Camera2) && (Camera2 != nullptr))
	//	{
	//		PlayerController->SetViewTargetWithBlend(Camera2,SmoothblendTime);
	//	}
	//}
}

void ACameraManager::SetCameraOne()
{
	if ((PlayerController->GetViewTarget() != Camera1) && (Camera1 != nullptr))
	{
		PlayerController->SetViewTargetWithBlend(Camera1,SmoothblendTime);
	}
}

void ACameraManager::SetCameraTwo()
{
	if ((PlayerController->GetViewTarget() != Camera2) && (Camera2 != nullptr))
	{
		PlayerController->SetViewTargetWithBlend(Camera2,SmoothblendTime);
	}
}

void ACameraManager::SetCameraThree()
{
	if ((PlayerController->GetViewTarget() != Camera3) && (Camera3 != nullptr))
	{
		PlayerController->SetViewTargetWithBlend(Camera3,SmoothblendTime);
	}
}

AActor* ACameraManager::GetCamera()
{
	AActor* CurrentCam;
	CurrentCam = PlayerController->GetViewTarget();
	return CurrentCam;
}

