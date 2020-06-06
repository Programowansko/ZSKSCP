// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "SCPLobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ASCPLobbyPlayerController::InitialSetup_Implementation()
{
	SaveGameCheck();
}

FText ASCPLobbyPlayerController::GetServName()
{
	return ServName;
}

void ASCPLobbyPlayerController::SaveGameCheck()
{
	SaveGameCheckBP();
}


void ASCPLobbyPlayerController::SetupLobbyMenu(FText ServerName)
{
	bShowMouseCursor = true;
	ServName = ServerName;

	CreateLobbyMenuBP();
}
