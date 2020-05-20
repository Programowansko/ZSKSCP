// Wiktor Ludwiniak 2020

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


	float Reach = 100.f; //Zasi�g postaci z kt�rej mo�e aktywowa�
	UInputComponent* InputComponent = nullptr;


	void SetupInputComponent(); //Funkcja kt�ra binduje okre�lon� akcje do przycisku
	void ToggleDoor();//Wywo�uje otwarcie/zamkni�cie drzwi
	FVector GetLineTraceEnd(FVector& PlayerViewPointLocation, FRotator& PlayerViewPointRotation) const; //Zwraca "zasi�g"

};
