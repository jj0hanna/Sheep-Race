// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(Root);
	//StaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetWorldScale3D(FVector(1.f,1.f,1.f));
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->SetupAttachment(Root);
	//Trigger->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}




