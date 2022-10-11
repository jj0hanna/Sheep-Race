#include "AC_DirectionTracker.h"

UAC_DirectionTracker::UAC_DirectionTracker()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAC_DirectionTracker::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAC_DirectionTracker::AddCount()
{
	if (!bDoCount) return;
	
	Count++;
	if (Count >= MaxWrong)
	{
		bDoCount = false;
		OnBadDirection();
	}
}

void UAC_DirectionTracker::ResetCount()
{
	Count = 0;
	bDoCount = true;
	OnGoodDirection();
}
