// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCPInventoryComponent.generated.h"

// Blueprints will bind this to update UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

class USCPItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPZSK_API USCPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USCPInventoryComponent();

	/*Add specified item to inventory*/
	UFUNCTION(BlueprintCallable)
	bool AddItem(USCPItem* Item);

	/*Remove specified item from inventory*/
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(USCPItem* Item);

	/*Default items in player's inventory*/
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<USCPItem*> DefaultItems;

	/*Max inventory capacity*/
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<USCPItem*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
