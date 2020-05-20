// Wiktor Ludwiniak 2020


#include "SCPOpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
USCPOpenDoor::USCPOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USCPOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentHeight = GetOwner()->GetActorLocation().Z;
	InitialHeight = CurrentHeight;
	OpenHeight += CurrentHeight;
	/*
	Wylicza i ustawia odpowiednie wartoœci otwierania i zamykania
	*/


}


float USCPOpenDoor::GetInitial()
{
	return InitialHeight;
}

float USCPOpenDoor::GetOpenHeight()
{
	return OpenHeight;
}

float USCPOpenDoor::GetCurrent()
{
	return CurrentHeight;
}

// Called every frame
void USCPOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bIsOpen == false) {

		OpenDoor(DeltaTime);

	}
	else {


		CloseDoor(DeltaTime);
	}

}

void USCPOpenDoor::OpenDoor(float DeltaTime)
{

	FVector Current = GetOwner()->GetActorLocation();
	Current.Z = CurrentHeight = FMath::FInterpConstantTo(CurrentHeight, OpenHeight, DeltaTime, OpenPerSec);

	GetOwner()->SetActorLocation(Current);
}

void USCPOpenDoor::CloseDoor(float DeltaTime)
{

	FVector Current = GetOwner()->GetActorLocation();
	Current.Z = CurrentHeight = FMath::FInterpConstantTo(CurrentHeight, InitialHeight, DeltaTime, ClosePerSec);

	GetOwner()->SetActorLocation(Current);

}
