// Wiktor Ludwiniak 2020

#include "SCPGrabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "SCPOpenDoor.h"


#define OUT
// Sets default values for this component's properties
USCPGrabber::USCPGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USCPGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();

}

void USCPGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();//Pobiera komponent odpowiedzialny za interakcje
	if (InputComponent) {
		InputComponent->BindAction("ToogleDoor", IE_Pressed, this, &USCPGrabber::ToggleDoor);//Przypisanie pod przyci�ni�cie wykonywania danej funkcji. Pierwszym sk�adnikiem jest nazwa zmapowanej akcji ustawionej w engine->input
	}

}



void USCPGrabber::ToggleDoor()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd = GetLineTraceEnd(PlayerViewPointLocation, PlayerViewPointRotation); //Zwraca "zasi�g"

	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParam
	);//Pobiera obiekt w naszym zasi�gu i przypisuje go do pierwszego argumentu

	if (Hit.GetActor()) {
		USCPOpenDoor* actor = Hit.GetActor()->FindComponentByClass<USCPOpenDoor>();//Pobiera wska�nik na klas� USCPOpenDoor Zawartej w aktorze
		if (actor) {//sprawdza czy aktor zawiera� ww. klase 
			if (!actor->bIsOpen)//Sprawdza czy drzwi nie s� otwarte 
			{
				if (actor->GetCurrent() == actor->GetOpenHeight()) {//Zmieni flag� obiektu gdy b�dzie w pe�ni z otwarty
					actor->bIsOpen = true;
				}
			}
			else
			{
				if (actor->GetCurrent() == actor->GetInitial()) {//Zmieni flag� obiektu gdy b�dzie w pe�ni zamkni�ty
					actor->bIsOpen = false;
				}
			}
		}

	}
}



// Called every frame
void USCPGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}




FVector USCPGrabber::GetLineTraceEnd(FVector& PlayerViewPointLocation, FRotator& PlayerViewPointRotation) const
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}