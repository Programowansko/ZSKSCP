// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Wiktor Ludwiniak

#include "SCPGrabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "SCPInteractable.h"
#include "DrawDebugHelpers.h"


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
		InputComponent->BindAction("Interact", IE_Pressed, this, &USCPGrabber::ToggleDoor);//Przypisanie pod przyci�ni�cie wykonywania danej funkcji. Pierwszym sk�adnikiem jest nazwa zmapowanej akcji ustawionej w engine->input
	}

}


void USCPGrabber::ToggleDoor()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd = GetLineTraceEnd(PlayerViewPointLocation, PlayerViewPointRotation); //Zwraca "zasięg"

	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParam
	);//Pobiera obiekt w naszym zasięgu i przypisuje go do pierwszego argumentu

	AActor* HitActor = Hit.GetActor();

	UE_LOG(LogTemp, Log, TEXT("Hit object %s"), *LineTraceEnd.ToString());

	if (HitActor) {
		USCPInteractable* InteractableActor = HitActor->FindComponentByClass<USCPInteractable>();//Pobiera wskaźnik na klasę USCPInteractable Zawartej w aktorze
		InteractableActor->InteractWithObject(Hit, GetOwner());
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