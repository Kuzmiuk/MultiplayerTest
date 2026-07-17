#include "OverheadWidget.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		break;
	case ENetRole::ROLE_AutonomousProxy:
		break;
	case ENetRole::ROLE_SimulatedProxy:
		break;
	case ENetRole::ROLE_None:
		break;
	}

	APlayerState* PlayerState = InPawn->GetPlayerState();
	FString PlayerName = PlayerState ? PlayerState->GetPlayerName() : TEXT("Unknown");
	SetDisplayText(PlayerName);
}

void UOverheadWidget::ShowPlayerName(APawn* InPawn)
{
	if (InPawn == nullptr) return;

	if (APlayerState* PlayerState = InPawn->GetPlayerState())
	{
		SetDisplayText(PlayerState->GetPlayerName());
	}

}

void UOverheadWidget::NativeDestruct()
{
	Super::NativeDestruct();

	RemoveFromParent();
}