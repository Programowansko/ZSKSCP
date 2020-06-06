// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Wiktor Ludwiniak

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCPGrabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SCPZSK_API USCPGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USCPGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*Zasięg postaci z której może aktywować*/
	UPROPERTY(EditDefaultsOnly, Category = "Grabber")
	float Reach = 200.f;

	UInputComponent* InputComponent = nullptr;


	void SetupInputComponent(); //Funkcja która binduje określoną akcje do przycisku
	void ToggleDoor();//Wywołuje otwarcie/zamknięcie drzwi
	FVector GetLineTraceEnd(FVector& PlayerViewPointLocation, FRotator& PlayerViewPointRotation) const; //Zwraca "zasięg"

};
