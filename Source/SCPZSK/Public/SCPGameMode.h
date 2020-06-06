// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas, Jakub Mrugalski

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SCPGameMode.generated.h"

enum class EWaveState : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);

class ASCPCharacter;

/**
 * 
 */
UCLASS()
class SCPZSK_API ASCPGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	FTimerHandle TimerHandle_NextSpawnWaveStart;

	int32 WaveCount;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	float TimeBetweenWaves;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	TSubclassOf<ASCPCharacter> ChaosPlayerClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	TSubclassOf<ASCPCharacter> MTFPlayerClass;

	// Spawn dead players as new class
	void SpawnDeadPlayers(TSubclassOf<ASCPCharacter> NewPlayerClass);

	// Set timer for the next wave
	void PrepareForNextSpawnWave();

	// Check who's alive
	void CheckEndGame();

	// Show UI for GameOver
	void GameOver();

	void SetWaveState(EWaveState NewState);

public:

	ASCPGameMode();

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnActorKilled OnActorKilled;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	TArray<TSubclassOf<AActor>> TilesetToSpawn;

	UFUNCTION(Reliable, Server)
	void SpawnTilesets();

};
