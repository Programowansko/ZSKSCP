// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Jakub Mrugalski

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCPElevator.generated.h"

class UBoxComponent;

UCLASS()
class SCPZSK_API ASCPElevator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASCPElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Teleportation delay in seconds*/
	UPROPERTY(EditDefaultsOnly, Category = "Elevator")
		float ElevatorDelay;

	UBoxComponent* TeleportZone;

	void TeleportPlayers();

	FVector RelativePosition;
	FRotator RelativeRotation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Elevator")
		bool bIsOpened;

	UPROPERTY(EditAnywhere, Category = "Elevator")
		AActor* TargetElevator;

	UFUNCTION()
		void InteractWithElevator();
};
