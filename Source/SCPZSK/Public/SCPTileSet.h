// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Jakub Mrugalski

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCPTileSet.generated.h"

class ASCPElevator;

UCLASS()
class SCPZSK_API ASCPTileSet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASCPTileSet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "TileSet")
	TArray<TSubclassOf<AActor>> Room;

	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditDefaultsOnly, Category = "TileSet")
	TSubclassOf<AActor> SpawnPointClass;

	UPROPERTY(EditDefaultsOnly, Category = "TileSet")
	TArray<TSubclassOf<AActor>> Tesla;

	TArray<AActor*> TeslaSpawnPoints;

	UPROPERTY(EditDefaultsOnly, Category = "TileSet")
	TSubclassOf<AActor> TeslaSpawnPointClass;

	TArray<AActor*> ElevatorComponents;

	UPROPERTY(EditDefaultsOnly, Category = "TileSet")
	TSubclassOf<AActor> ElevatorClass;

	ASCPElevator* FindElevator(FName Side, FName Floor, FName System);

	bool ConnectElevator(FName Side, FName CurrentFloor, FName TargetFloor, FName System);

public:
	UFUNCTION(Reliable, Server)
		void Initialize();

	UFUNCTION(Reliable, Server)
		void SpawnRooms();

	UFUNCTION(Reliable, Server)
		void SpawnTeslas();

	UFUNCTION(Reliable, Server)
		void ConnectElevators();

	TArray<ASCPElevator*> Elevators;

};
