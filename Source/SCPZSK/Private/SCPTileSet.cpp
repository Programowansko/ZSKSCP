// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Jakub Mrugalski

#include "SCPTileSet.h"
#include "Kismet/GameplayStatics.h"
#include "SCPElevator.h"


// Sets default values
ASCPTileSet::ASCPTileSet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void ASCPTileSet::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

ASCPElevator* ASCPTileSet::FindElevator(FName Side, FName Floor, FName System)
{
	for (int i = 0; i < ElevatorComponents.Num(); i++)
	{
		if (ElevatorComponents[i]->ActorHasTag(Side) && ElevatorComponents[i]->ActorHasTag(Floor) && ElevatorComponents[i]->ActorHasTag(System))
		{
			return (Cast<ASCPElevator>(ElevatorComponents[i]));
		}
	}
	return nullptr;
}

bool ASCPTileSet::ConnectElevator(FName Side, FName CurrentFloor, FName TargetFloor, FName System)
{
	ASCPElevator* FirstElevator = FindElevator(Side, CurrentFloor, System);
	ASCPElevator* SecondElevator = FindElevator(Side, TargetFloor, System);

	if (FirstElevator && SecondElevator)
	{
		FirstElevator->TargetElevator = Cast<AActor>(SecondElevator);
		SecondElevator->TargetElevator = Cast<AActor>(FirstElevator);
		return true;
	}
	return false;
}

void ASCPTileSet::Initialize_Implementation()
{
	UGameplayStatics::GetAllActorsOfClass(this, SpawnPointClass, SpawnPoints);
	SpawnRooms();

	UGameplayStatics::GetAllActorsOfClass(this, TeslaSpawnPointClass, TeslaSpawnPoints);
	SpawnTeslas();

	UGameplayStatics::GetAllActorsOfClass(this, ElevatorClass, ElevatorComponents);
	ConnectElevators();

}

void ASCPTileSet::SpawnRooms_Implementation() //Spawns rooms on each floor
{
	UWorld* WRLD = GetWorld();
	FVector SpawnLocation;
	FRotator SpawnRotation;

	for (int i = 0; i < 2; i++)//Spawns elevator A & B.
	{
		int RandomSpawnPoint = FMath::RandRange(0, SpawnPoints.Num() - 1);

		SpawnLocation = SpawnPoints[RandomSpawnPoint]->GetActorLocation();
		SpawnRotation = SpawnPoints[RandomSpawnPoint]->GetActorRotation();
		WRLD->SpawnActor(Room[i], &SpawnLocation, &SpawnRotation);
		SpawnPoints.RemoveAt(RandomSpawnPoint);
	}

	for (int i = 0; i < SpawnPoints.Num(); i++) //Spawns rest of the rooms.
	{
		SpawnLocation = SpawnPoints[i]->GetActorLocation();
		SpawnRotation = SpawnPoints[i]->GetActorRotation();
		WRLD->SpawnActor(Room[2], &SpawnLocation, &SpawnRotation);

	}


}

void ASCPTileSet::SpawnTeslas_Implementation()
{
	UWorld* WRLD = GetWorld();
	FVector SpawnLocation;
	FRotator SpawnRotation;

	int TeslasToSpawn = TeslaSpawnPoints.Num() / 4; //Stores amount of spawnpoints for teslas based on amount of 2-way corridors.

	for (int i = 0; i < TeslasToSpawn; i++)
	{
		int RandomSpawnPoint = FMath::RandRange(0, TeslaSpawnPoints.Num() - 1);

		SpawnLocation = TeslaSpawnPoints[RandomSpawnPoint]->GetActorLocation();
		SpawnRotation = TeslaSpawnPoints[RandomSpawnPoint]->GetActorRotation();
		WRLD->SpawnActor(Tesla[FMath::RandRange(0, Tesla.Num() - 1)], &SpawnLocation, &SpawnRotation);

		TeslaSpawnPoints.RemoveAt(RandomSpawnPoint);
	}
}

void ASCPTileSet::ConnectElevators_Implementation()
{
	if (Role == ROLE_Authority)
	{
		ConnectElevator("Left", "HCZ", "LCZ", "A");
		ConnectElevator("Left", "HCZ", "LCZ", "B");
		ConnectElevator("Right", "HCZ", "LCZ", "A");
		ConnectElevator("Right", "HCZ", "LCZ", "B");
	}
};


