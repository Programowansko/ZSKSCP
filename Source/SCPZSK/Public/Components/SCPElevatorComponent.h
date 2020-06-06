// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Jakub Mrugalski

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCPElevatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPZSK_API USCPElevatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USCPElevatorComponent();

protected:

public:	
	
	void Interact();
		
};
