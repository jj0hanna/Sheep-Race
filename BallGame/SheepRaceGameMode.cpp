#include "SheepRaceGameMode.h"

#include "GP4T4/Checkpoint.h"
#include "GP4T4/CheckpointTracker.h"
#include "Kismet/GameplayStatics.h"


void ASheepRaceGameMode::OnLevelStart_Implementation()
{
	//Gets the Checkpoint tracker in the level
	ACheckpointTracker* CheckpointTracker = Cast<ACheckpointTracker>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheckpointTracker::StaticClass()));
	if (!CheckpointTracker)
		return;
	
	//Subscribes to trackers delegate
	CheckpointTracker->OnFinishedRace.AddDynamic(this, &ASheepRaceGameMode::OnPlayerFinishedRace);
}

void ASheepRaceGameMode::StartRaceCountDown_Implementation()
{
}

void ASheepRaceGameMode::StartRace_Implementation()
{
}

void ASheepRaceGameMode::EndRace_Implementation()
{
	
}

void ASheepRaceGameMode::OnPlayerFinishedRace_Implementation(APawn* Pawn)
{
}
