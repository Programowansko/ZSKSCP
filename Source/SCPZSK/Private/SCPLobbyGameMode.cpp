// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "SCPLobbyGameMode.h"
#include "SCPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "SCPLobbyPlayerController.h"
#include "TimerManager.h"

void ASCPLobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (HasAuthority())
	{
		AllPlayerControllers.Add(NewPlayer);
		UGameplayStatics::GetAllActorsOfClass(this, PlayerStartClass, SpawnPoints);
		
		SetupGameInstance();

		ASCPLobbyPlayerController* LobbyPC = Cast<ASCPLobbyPlayerController>(NewPlayer);
		LobbyPC->InitialSetup();
		LobbyPC->SetupLobbyMenu(ServerName);

		RespawnPlayer(NewPlayer);
	}
}

void ASCPLobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);

	RemoveFromArrays();

	EveryoneUpdate();
}

void ASCPLobbyGameMode::RespawnAllDeadPlayers()
{
	for (int i=0; i < AllPlayerControllers.Num(); i++)
	{
		APlayerController* tPC = AllPlayerControllers[i];
		if (tPC && tPC->GetPawn() == nullptr)
		{
			RespawnPlayer(tPC);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Spawning players"));
}

TArray<APlayerController*> ASCPLobbyGameMode::GetAllPlayerControllers()
{
	return AllPlayerControllers;
}

int ASCPLobbyGameMode::GetCurrentNumberOfPlayers()
{
	return CurrentPlayers;
}

int ASCPLobbyGameMode::GetMaxNumberOfPlayers()
{
	return MaxPlayers;
}

void ASCPLobbyGameMode::SetServerName(FText NewServerName)
{
	ServerName = NewServerName;
}

void ASCPLobbyGameMode::SetMaxPlayers(int NewMaxPlayers)
{
	MaxPlayers = NewMaxPlayers;
}

void ASCPLobbyGameMode::RemoveAtAllPlayersControllers(int IndexToRemove)
{
	AllPlayerControllers.RemoveAt(IndexToRemove);
}

void ASCPLobbyGameMode::EveryoneUpdate_Implementation()
{
	CurrentPlayers = AllPlayerControllers.Num();

	if (CurrentPlayers > 0) 
	{
		UpdateBP();
	}
}

void ASCPLobbyGameMode::RespawnPlayer_Implementation(APlayerController * PC)
{
	APawn* PlayerPawn = PC->GetPawn();
	if(PlayerPawn)
	{
		PlayerPawn->Destroy();
	}

	int rand = FMath::RandRange(0, SpawnPoints.Num() - 1);

	RespawnPlayerBP(PC, SpawnPoints[rand]->GetActorTransform());

	EveryoneUpdate();
}

void ASCPLobbyGameMode::StartPlay()
{
	Super::StartPlay();

	FTimerHandle TimerHandle_NextRespawn;
	GetWorldTimerManager().SetTimer(TimerHandle_NextRespawn, this, &ASCPLobbyGameMode::RespawnAllDeadPlayers, 10.0f, true, 10.0f);
}
