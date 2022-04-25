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

	if (GetCurrentMesh())
	{
		TurnOffMesh(GetCurrentMesh());
	}
	SetCurrentMesh(SignalMesh);
}

void AQuestPlaceActor::ChangeCurrentMesh(WorldModes Mode)
{
	if (!bIsChangeableActorPlacedInside) return;
	TurnOffMesh(GetCurrentMesh());
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
	if(OnStartInteractEvent.IsBound())
	{
		OnStartInteractEvent.Broadcast();
	}
}