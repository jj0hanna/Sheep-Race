#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PowerUpPickup.generated.h"

UENUM(BlueprintType)
enum PowerUpType
{
	Shell		UMETA(DisplayName = "Shell"),
	Mine		UMETA(DisplayName = "Mine")
};

UCLASS()
class GP4T4_API APowerUpPickup : public APickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<PowerUpType> Type;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
