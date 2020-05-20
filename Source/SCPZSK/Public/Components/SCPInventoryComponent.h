// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable)
	bool AddItem(USCPItem* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(USCPItem* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<USCPItem*> DefaultItems;

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
