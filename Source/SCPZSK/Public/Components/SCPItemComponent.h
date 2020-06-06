// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCPItemComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPZSK_API USCPItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USCPItemComponent();

protected:

	/*Item to add*/
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class USCPItem* Item;

public:	

	/*Delete item from server*/
	UFUNCTION(Reliable, Server)
	void ServerInteract();

	/*Add Item to Players inventory*/
	void Interact(class AActor* PlayerCharacter);

};
