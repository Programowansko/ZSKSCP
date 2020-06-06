// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Wiktor Ludwiniak

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "SCPOpenDoor.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SCPZSK_API USCPOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USCPOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void Interact(); // Handle interaction with doors

	// Called every frame
	float GetInitial();//Zwraca początkową wysokość
	float GetOpenHeight();//Zwraca końcową wysokość 
	float GetCurrent();//Zwraca aktualną wysokość

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);//Otwiera drzwi
	void CloseDoor(float DeltaTime);//Zamyka drzwi 

	bool bIsOpen = true; //Flaga czy drzwi mają dążyć do otwarcia czy nie 
private:

	float InitialHeight;//Początkowa wysokość

	UPROPERTY(EditAnywhere)
	float OpenHeight = 90.f;//O ile mają się otworzyć drzwi (później wartosc zmieniana jest na ostateczną wysokość)

	float CurrentHeight;//Aktualna wysokosc





	UPROPERTY(EditAnywhere)
		float OpenPerSec = 30;//Prędkośc otwierania 
	UPROPERTY(EditAnywhere)
		float ClosePerSec = 30;//Prędkość zamykania

};