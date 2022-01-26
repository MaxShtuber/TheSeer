// 10.8 Team. All rights reserved.

#include "Dev/BasePageActor.h"
#include "SGameModeBase.h"

void ABasePageActor::OnStartInteract()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnTakenPage(PageNumber);
	Destroy();
}