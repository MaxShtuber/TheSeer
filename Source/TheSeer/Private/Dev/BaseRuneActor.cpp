// 10.8 Team. All rights reserved.

#include "Dev/BaseRuneActor.h"
#include "SGameModeBase.h"

ABaseRuneActor::ABaseRuneActor()
{
	RuneMesh = CreateDefaultSubobject<UStaticMeshComponent>("RuneMesh");
}

void ABaseRuneActor::OnStartInteract()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->AddTakenRune(RuneTag);
	Destroy();
}

