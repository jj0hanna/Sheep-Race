#include "A_Camera3.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AA_Camera3::AA_Camera3()
{
	PrimaryActorTick.bCanEverTick = true;
	//Root
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = Root;

	//Springarm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	
	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
}

void AA_Camera3::BeginPlay()
{
	Super::BeginPlay();
	SpringArm->TargetArmLength = DefaultArmLength;
	Camera->SetFieldOfView(DefaultFieldOfView);
	CameraSpringRotationSpeed = DefaultCameraRotationSpeed;
}

void AA_Camera3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerPrimitiveComponent)
	{
		if (ActiveSpline)
		{
			LookAtPlayer();
			SetCameraLocationAndRotation();
		}
		if (bChangeFieldOfView)
		{
			ChangeFieldOfView(DeltaTime);
		}
	}
}

void AA_Camera3::SetCameraLocationAndRotation()
{
	PlayerComponentLocation = PlayerPrimitiveComponent->GetComponentLocation();
	if (ActiveSpline)
	{
		const float InputKey = ActiveSpline->FindInputKeyClosestToWorldLocation(PlayerComponentLocation);
		const FVector TargetLocation = ActiveSpline->GetLocationAtSplineInputKey(InputKey, ESplineCoordinateSpace::World);
		const FVector SpringArmLocation = SpringArm->GetComponentLocation();
		
		SetActorLocation(FMath::Lerp(SpringArmLocation, TargetLocation, InterpSpeed * GetWorld()->GetDeltaSeconds()));
		SetCameraRotation();
	}
}
void AA_Camera3::SetCameraRotation()
{
	const FVector PlayerMeshLocation = PlayerPrimitiveComponent->GetComponentLocation();
	const float InputKey = ActiveSpline->FindInputKeyClosestToWorldLocation(PlayerMeshLocation);
	const FRotator TargetRotation = ActiveSpline->GetRotationAtSplineInputKey(InputKey, ESplineCoordinateSpace::World);

	PlayerVelocity = PlayerPrimitiveComponent->GetComponentVelocity();
	const FRotator SpringArmRotation = SpringArm->GetComponentRotation();
	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(),Camera->GetComponentLocation() + PlayerVelocity);

	FRotator B = FRotator(TargetRotation.Pitch,LookAtRotation.Yaw,TargetRotation.Roll);

	if (abs(PlayerVelocity.X) > 100.f)
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Black, (TEXT("Player Velocity.X Bigger then 100")));
		SpringArm->SetWorldRotation(FMath::Lerp(SpringArmRotation,B, CameraSpringRotationSpeed * GetWorld()->GetDeltaSeconds()));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Red, (TEXT("Player Velocity.X smaler then 100, not rotating")));
	}
	if (abs(PlayerVelocity.Y) > 100.f)
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::White, (TEXT("Player Velocity.Y Bigger then 100")));
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Green, (TEXT("Player Velocity.Y Bigger then 100")));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,0.f,FColor::Green, (TEXT("Player Velocity.Y smaler then 100, not rotating")));
	}
}

void AA_Camera3::LookAtPlayer() const
{
	if (PlayerPrimitiveComponent)
	{
		const FRotator SetLookAtRotation = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(),PlayerPrimitiveComponent->GetComponentLocation());
		Camera->SetWorldRotation(SetLookAtRotation);
	}
}

void AA_Camera3::SmoothSplineChange()
{
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE,10.f,FColor::Black,FString::Printf(TEXT("Active spline: %s"), *ActiveSpline->GetReadableName()));
	//When we swap spline, lerp between those positions
}

void AA_Camera3::PlayerIsFlippedCameraChange(bool bIsFlipped)
{
	bPlayerIsFlipped = bIsFlipped; // this could be a subscription insted. Lerp the length changes?
	if (bPlayerIsFlipped)
	{
		SpringArm->TargetArmLength = PlayerFlippedArmlength;
		CameraSpringRotationSpeed = CameraSpringRotationSpeedWhenFlipped;
	}
	else
	{
		SpringArm->TargetArmLength = DefaultArmLength;
		CameraSpringRotationSpeed = DefaultCameraRotationSpeed;
	}
}

void AA_Camera3::SetCameraStartLocation() const
{
	if (PlayerPrimitiveComponent)
	{
		const float InputKeyClosestToPlayerLocation = ActiveSpline->FindInputKeyClosestToWorldLocation(PlayerPrimitiveComponent->GetComponentLocation());
		const FVector LocationAtInputKey = ActiveSpline->GetLocationAtSplineInputKey(InputKeyClosestToPlayerLocation, ESplineCoordinateSpace::World);// 2 inputkey location
		
		FVector DirectionAtSplineInputKey = ActiveSpline->GetDirectionAtSplineInputKey(InputKeyClosestToPlayerLocation,ESplineCoordinateSpace::World);

		auto LenghtBetweenBAndInputKey = (LocationAtInputKey - PlayerPrimitiveComponent->GetComponentLocation()).Length(); //a.lenght
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,10.f,FColor::White, ((LocationAtInputKey - PlayerPrimitiveComponent->GetComponentLocation()).ToString()));
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE,10.f,FColor::Red,FString::Printf(TEXT("LenghtBetweenBAndInputKey: %f"), LenghtBetweenBAndInputKey));

		auto LenghtBetweenPlayerAndArmlenghtEnd = FMath::Sqrt(FMath::Pow(LenghtBetweenBAndInputKey,2) + FMath::Pow(SpringArm->TargetArmLength,2));
		auto AngleToRotate = FMath::RadiansToDegrees(FMath::Asin(LenghtBetweenBAndInputKey/LenghtBetweenPlayerAndArmlenghtEnd));  // convert AngleToRotate from radians to degrees

		auto SideOfSplineLocation = LocationAtInputKey - PlayerPrimitiveComponent->GetComponentLocation();
		if (SideOfSplineLocation.Y > 0.f) //Depending on which side the player is decides which side the arm should rotate - or + 
		{
			AngleToRotate *= -1.f;
		}
		SpringArm->SetRelativeRotation(FRotator(0.f,AngleToRotate,0.f));
	}
}
void AA_Camera3::ChangeFieldOfView(float DeltaTime) // have a lib for settings insted or call this in player tick insted
{
	if (abs(PlayerVelocity.X) > 3800.f)
	{
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView,FieldOfViewTr1, FieldOfViewChangeSpeed * DeltaTime));
	}
	if (abs(PlayerVelocity.X) > 4000.f)
	{
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView,FieldOfViewTr2, FieldOfViewChangeSpeed * DeltaTime));
	}
	if (abs(PlayerVelocity.X) > 5000.f)
	{
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView,FieldOfViewTr3, FieldOfViewChangeSpeed * DeltaTime));
	}
	else
	{
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView,DefaultFieldOfView, FieldOfViewChangeSpeed * DeltaTime));
	}
}
