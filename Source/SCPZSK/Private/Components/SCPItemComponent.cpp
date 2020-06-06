// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "Components/SCPItemComponent.h"
#include "Components/SCPInventoryComponent.h"
#include "SCPCharacter.h"

// Sets default values for this component's properties
USCPItemComponent::USCPItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void USCPItemComponent::Interact(AActor* PlayerCharacter)
{
	if(GetOwner()->Role < ROLE_Authority)
		ServerInteract();

	UE_LOG(LogTemp, Log, TEXT("Adding item to inventory"));
	USCPInventoryComponent* InventoryComp = PlayerCharacter->FindComponentByClass<USCPInventoryComponent>();
	InventoryComp->AddItem(Item);
}

void USCPItemComponent::ServerInteract_Implementation()
{
	GetOwner()->Destroy();
}
