// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Wiktor Ludwiniak

#include "SCPInteractable.h"
#include "SCPOpenDoor.h"
#include "SCPItem.h"
#include "Components/SCPItemComponent.h"

// Sets default values for this component's properties
USCPInteractable::USCPInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USCPInteractable::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USCPInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USCPInteractable::InteractWithObject(FHitResult Hit, AActor* PlayerChar)
{
	USCPOpenDoor* DoorsActor = Hit.GetActor()->FindComponentByClass<USCPOpenDoor>();//Pobiera wskaźnik na klasę UOpenDoor Zawartej w aktorze
	if (DoorsActor) {//sprawdza czy aktor zawierał ww. klase 
		DoorsActor->Interact();
	}

	USCPItemComponent* ItemActor = Hit.GetActor()->FindComponentByClass<USCPItemComponent>();
	if (ItemActor) {
		UE_LOG(LogTemp, Log, TEXT("Interacting with Item"));
		ItemActor->Interact(PlayerChar);
	}
	
	/*
	USCPElevatorComponent* ElevatorActor = Hit.GetActor()->FindComponentByClass<USCPElevatorComponent>();
	if (ElevatorActor) {
		ElevatorActor->Interact();
	}
	*/
}


