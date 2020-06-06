// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Jakub Mrugalski

#include "Components/SCPElevatorComponent.h"
#include "SCPElevator.h"

// Sets default values for this component's properties
USCPElevatorComponent::USCPElevatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USCPElevatorComponent::Interact()
{
	Cast<ASCPElevator>(GetOwner())->InteractWithElevator();
}
