// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SCPGameState.generated.h"

UENUM(BlueprintType)
enum class EWaveState : uint8
{
	WaitingToSpawn,

	SpawningPlayers,

	GameOver,
};

/**
 * 
 */
UCLASS()
class SCPZSK_API ASCPGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UFUNCTION()
	void OnRep_WaveState(EWaveState OldState);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
	void WaveStateChanged(EWaveState NewState, EWaveState OldState);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WaveState, Category = "GameState")
	EWaveState WaveState;


public:

	void SetWaveState(EWaveState NewState);
};
