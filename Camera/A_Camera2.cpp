#include "A_Camera2.h"
#include "Camera/CameraComponent.h"

AA_Camera2::AA_Camera2()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	//Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	//RootComponent = Root;
//
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(Root);
}

void AA_Camera2::BeginPlay()
{
	Super::BeginPlay();

	//APlayerController* Controller1 = GetWorld()->GetFirstPlayerController();
	//Controller1->SetViewTarget(this);
	//
	//FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetFocalLocation();
	//FVector CameraPos = GetActorLocation();
//
	//DistanceBetween = PlayerLocation - CameraPos;
	
}


void AA_Camera2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	//FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetFocalLocation();
	//FVector CameraPos = GetActorLocation();
//
	//CameraPos = FMath::Lerp(CameraPos,PlayerLocation - DistanceBetween,FollowSpeed * DeltaTime);
	//SetActorLocation(CameraPos);


}

