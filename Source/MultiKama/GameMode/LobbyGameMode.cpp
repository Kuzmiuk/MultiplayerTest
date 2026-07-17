// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "MultiplayerSessionsSubsystem.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	StartGame();
}

void ALobbyGameMode::StartGame()
{
    const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

    UMultiplayerSessionsSubsystem* Subsystem =
        GetGameInstance()->GetSubsystem<UMultiplayerSessionsSubsystem>();

    if (!Subsystem) return;

    if (NumberOfPlayers != Subsystem->DesiredNumPublicConnections) return;

    UWorld* World = GetWorld();
    if (!World) return;

    bUseSeamlessTravel = true;

    const FString Map =
        (Subsystem->DesiredMatchType == "Teams")
        ? TEXT("/Game/Maps/Team?listen")
        : TEXT("/Game/Maps/Game?listen");

    World->ServerTravel(Map);
}