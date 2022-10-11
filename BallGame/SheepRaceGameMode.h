#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SheepRaceGameMode.generated.h"

UCLASS()
class GP4T4_API ASheepRaceGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLevelStart(); // spawn players, loadingscreen, DisableMovment

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartRaceCountDown(); //Start RaceCountdown

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartRace(); //EnableMovment, start playertimer

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerFinishedRace(APawn* Pawn);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndRace(); //Disablemovment on the player that finished the race, When both finished = show win menu 

};
