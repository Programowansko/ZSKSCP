// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SCPLobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCPZSK_API ASCPLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	FText ServName;

public:

	UFUNCTION(BlueprintCallable)
	FText GetServName();

	UFUNCTION(Reliable, Client)
	void InitialSetup();

	void SaveGameCheck();

	UFUNCTION(BlueprintImplementableEvent)
	void SaveGameCheckBP();

	void SetupLobbyMenu(FText ServerName);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateLobbyMenuBP();
};
