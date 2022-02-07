// 10.8 Team. All rights reserved.

#include "Dev/QuestPlaceActor.h"

AQuestPlaceActor::AQuestPlaceActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SignalMesh = CreateDefaultSubobject<UStaticMeshComponent>("SignalMesh");
	SignalMesh->SetupAttachment(GetRootComponent());
}

void AQuestPlaceActor::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentMesh)
	{
		TurnOffMesh(CurrentMesh);
	}
	CurrentMesh = SignalMesh;
}

void AQuestPlaceActor::ChangeCurrentMesh(WorldModes Mode)
{
	if (!bIsChangeableActorPlacedInside) return;
	TurnOffMesh(CurrentMesh);
	Super::ChangeCurrentMesh(Mode);
}

void AQuestPlaceActor::SetChangeableActorPlacedInside(bool NewValue)
{
	if (bIsChangeableActorPlacedInside) return;
	bIsChangeableActorPlacedInside = NewValue;
}

void AQuestPlaceActor::OnStartInteract()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	SetChangeableActorPlacedInside(true);
	ChangeCurrentMesh(GameMode->GetWorldMode());
}