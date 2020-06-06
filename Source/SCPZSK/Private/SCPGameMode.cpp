// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "SCPGameMode.h"
#include "Components/SCPHealthComponent.h"
#include "SCPGameState.h"
#include "TimerManager.h"

ASCPGameMode::ASCPGameMode()
{
	// Time between player spawns [s]
	TimeBetweenWaves = 10.0f;

	GameStateClass = ASCPGameState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}

void ASCPGameMode::SpawnDeadPlayers(TSubclassOf<ASCPCharacter> NewPlayerClass)
{
	// @TODO: Change restarting player to spawn as NewPlayerClass
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			RestartPlayer(PC);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Spawning players"));
	SetWaveState(EWaveState::SpawningPlayers);
}

void ASCPGameMode::PrepareForNextSpawnWave()
{
	TSubclassOf<ASCPCharacter> NewClassToSpawn;

	int i = 1;

	switch (i)
	{
	case 1:
		NewClassToSpawn = ChaosPlayerClass;
		break;
	default:
		NewClassToSpawn = MTFPlayerClass;
		break;
	}

	SetWaveState(EWaveState::WaitingToSpawn);

	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &ASCPGameMode::SpawnDeadPlayers, NewClassToSpawn);
	GetWorldTimerManager().SetTimer(TimerHandle_NextSpawnWaveStart, RespawnDelegate, TimeBetweenWaves, true, TimeBetweenWaves);
}

void ASCPGameMode::CheckEndGame()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			USCPHealthComponent* HealthComp = Cast<USCPHealthComponent>(MyPawn->GetComponentByClass(USCPHealthComponent::StaticClass()));
			if (HealthComp && HealthComp->GetHealth() > 0.0f)
			{
				PC->GetPawn()->GetClass();
				return;
			}
		}
	}

	// No player alive
	GameOver();
}

void ASCPGameMode::GameOver()
{

	GetWorldTimerManager().ClearTimer(TimerHandle_NextSpawnWaveStart);

	// @TODO: Display UI for everyone
	SetWaveState(EWaveState::GameOver);

	UE_LOG(LogTemp, Log, TEXT("GAME OVER! Players died!"));
}

void ASCPGameMode::SetWaveState(EWaveState NewState)
{
	ASCPGameState* GS = GetGameState<ASCPGameState>();
	if (ensureAlways(GS))
	{
		GS->SetWaveState(NewState);
	}
}

void ASCPGameMode::StartPlay()
{
	Super::StartPlay();

	SpawnTilesets();

	PrepareForNextSpawnWave();
}

void ASCPGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckEndGame();
}

void ASCPGameMode::SpawnTilesets_Implementation()
{
	UWorld* WRLD = GetWorld();

	FVector location = FVector(0.0f, 0.0f, 0.0f);
	FRotator rotation = FRotator(0.0f, 0.0f, 0.0f);

	if(TilesetToSpawn[0])
		WRLD->SpawnActor(TilesetToSpawn[0], &location, &rotation); //Spawns HCZ
	else
		UE_LOG(LogTemp, Log, TEXT("TilesetToSpawn[0] is nullptr"));

	location = FVector(20000.0f, 0.0f, 0.0f);
	rotation = FRotator(0.0f, 0.0f, 0.0f);

	if (TilesetToSpawn[1])
		WRLD->SpawnActor(TilesetToSpawn[1], &location, &rotation); //Spawns LCZ
	else
		UE_LOG(LogTemp, Log, TEXT("TilesetToSpawn[1] is nullptr"));


}