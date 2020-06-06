// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SCPLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCPZSK_API ASCPLobbyGameMode : public AGameMode
{
	GENERATED_BODY()


	TArray<APlayerController*> AllPlayerControllers;
	TArray<AActor*> SpawnPoints;
	FText ServerName;
	int MaxPlayers;
	int CurrentPlayers;

	void PostLogin(APlayerController * NewPlayer) override;

	void Logout(AController * Exiting) override;

	/*Spawn the Player as the Base Character when arriving at the Lobby Menu*/
	UFUNCTION(Reliable, Server)
	void RespawnPlayer(APlayerController * PC);	

	void RespawnAllDeadPlayers();

	/*Updates all connected players lobby information when called*/
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void EveryoneUpdate();

public:

	UFUNCTION(BlueprintCallable)
	TArray<APlayerController*> GetAllPlayerControllers();

	UFUNCTION(BlueprintCallable)
	int GetCurrentNumberOfPlayers();

	UFUNCTION(BlueprintCallable)
	int GetMaxNumberOfPlayers();

	UFUNCTION(BlueprintCallable)
	void SetServerName(FText NewServerName);

	UFUNCTION(BlueprintCallable)
	void SetMaxPlayers(int NewMaxPlayers);

	UFUNCTION(BlueprintCallable)
	void RemoveAtAllPlayersControllers(int IndexToRemove);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASCPCharacter> BaseCharacterClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APlayerStart> PlayerStartClass;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupGameInstance();

	UFUNCTION(BlueprintImplementableEvent)
	void RespawnPlayerBP(APlayerController * PC, FTransform SpawnTransform);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBP();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveFromArrays();

	virtual void StartPlay() override;
};
