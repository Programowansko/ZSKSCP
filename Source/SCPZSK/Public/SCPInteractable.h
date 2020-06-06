// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Wiktor Ludwiniak

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCPInteractable.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SCPZSK_API USCPInteractable : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USCPInteractable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InteractWithObject(FHitResult Hit, AActor* PlayerChar);

};
