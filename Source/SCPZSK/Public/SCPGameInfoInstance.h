// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SCPGameInfoInstance.generated.h"


class UUserWidget;

/**
 *
 */
UCLASS()
class SCPZSK_API USCPGameInfoInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	USCPGameInfoInstance();

	UPROPERTY(EditAnywhere, Category = "ServerSettings")
		int MaxPlayers;

	UPROPERTY(EditAnywhere, Category = "ServerSettings")
		FName ServerName;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "GameInfo")
		FString PlayerSettingsSave;

	UPROPERTY(EditDefaultsOnly, Category = "GameInfo")
		bool bCreatedSaveFile;

	UPROPERTY(BlueprintReadWrite, Category = "GameInfo")
		FString ErrorString;

	APlayerController* PC;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> HostMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> ServerMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> LoadingScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> OptionsMenuWidgetClass;

	UUserWidget* MainMenu;
	UUserWidget* HostMenu;
	UUserWidget* ServerMenu;
	UUserWidget* OptionsMenu;
	UUserWidget* LoadingScreen;
	UUserWidget* ErrorDialog;

public:

	UFUNCTION(BlueprintCallable)
		void SaveGameCheck();

	UFUNCTION(BlueprintCallable)
		void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
		void ShowHostMenu();

	UFUNCTION(BlueprintCallable)
		void ShowServerMenu();

	UFUNCTION(BlueprintCallable)
		void ShowOptionsMenu();

	UFUNCTION(BlueprintCallable)
		void ShowLoadingScreen();

	UFUNCTION(BlueprintCallable)
		void LaunchLobby(int _MaxPlayers, FName _ServerName, bool bEnableLan);

	UFUNCTION(BlueprintCallable)
	FName GetServerName();

	UFUNCTION(BlueprintCallable)
	int GetMaxPlayers();
};
