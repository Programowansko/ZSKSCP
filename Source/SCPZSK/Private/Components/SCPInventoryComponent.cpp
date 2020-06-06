// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "Components/SCPInventoryComponent.h"
#include "SCPItem.h"
 
// Sets default values for this component's properties
USCPInventoryComponent::USCPInventoryComponent()
{
	Capacity = 8;
}


bool USCPInventoryComponent::AddItem(USCPItem* Item)
{
	// Check if player have capacity for item
	if(Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	OnInventoryUpdated.Broadcast();

	return true;
}

bool USCPInventoryComponent::RemoveItem(USCPItem* Item)
{
	if(Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);

		OnInventoryUpdated.Broadcast();

		return true;
	}

	return false;
}

// Called when the game starts
void USCPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
	
}

