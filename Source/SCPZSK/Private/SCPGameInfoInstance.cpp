// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "SCPGameInfoInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystemUtils.h"

USCPGameInfoInstance::USCPGameInfoInstance()
{
	PlayerSettingsSave = "PlayerSettingsSave";
	bCreatedSaveFile = false;
	ErrorString = "";
}

void USCPGameInfoInstance::SaveGameCheck()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerSettingsSave, 0))
	{
		ShowMainMenu();
		bCreatedSaveFile = true;
	}
	else
	{
		ShowOptionsMenu();
	}

}

void USCPGameInfoInstance::ShowMainMenu()
{
	if (!MainMenu)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
	}
	MainMenu->AddToViewport();
}

void USCPGameInfoInstance::ShowHostMenu()
{
	if (!HostMenu)
	{
		HostMenu = CreateWidget<UUserWidget>(this, HostMenuWidgetClass);
	}
	HostMenu->AddToViewport();
}

void USCPGameInfoInstance::ShowServerMenu()
{
	if (!ServerMenu) 
	{
		ServerMenu = CreateWidget<UUserWidget>(this, ServerMenuWidgetClass);
	}
	ServerMenu->AddToViewport();
}

void USCPGameInfoInstance::ShowOptionsMenu()
{
	if (!OptionsMenu)
	{
		OptionsMenu = CreateWidget<UUserWidget>(this, OptionsMenuWidgetClass);
	}
	OptionsMenu->AddToViewport();
}

void USCPGameInfoInstance::ShowLoadingScreen()
{
	if (!LoadingScreen)
	{
		LoadingScreen = CreateWidget<UUserWidget>(this, LoadingScreenWidgetClass);
	}
	LoadingScreen->AddToViewport();
}

void USCPGameInfoInstance::LaunchLobby(int _MaxPlayers, FName _ServerName, bool bEnableLan)
{
	MaxPlayers = _MaxPlayers;
	ServerName = _ServerName;

	ShowLoadingScreen();
	FOnlineSessionSettings ServerSettings;
	ServerSettings.bIsLANMatch = bEnableLan;

	IOnlineSubsystem* OSInst = IOnlineSubsystem::Get();
	IOnlineSessionPtr SessionInst = OSInst->GetSessionInterface();

	if (SessionInst->CreateSession(MaxPlayers, ServerName, ServerSettings))
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Lobby", true, "listen");
	}

}

FName USCPGameInfoInstance::GetServerName()
{
	return ServerName;
}

int USCPGameInfoInstance::GetMaxPlayers()
{
	return MaxPlayers;
}
