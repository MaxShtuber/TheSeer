// 10.8 Team. All rights reserved.

#include "Dev/BaseChangeableActor.h"
#include "Components/TextRenderComponent.h"

ABaseChangeableActor::ABaseChangeableActor()
{
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	TextComponent->SetupAttachment(GetRootComponent());
}

void ABaseChangeableActor::BeginPlay()
{
	Super::BeginPlay();

	TextComponent->SetText(ActivateDescription);
	TextComponent->SetVisibility(false);
}

void ABaseChangeableActor::SetMeshChangeable(bool NewMeshChangeable)
{
	bIsMeshChangeable = NewMeshChangeable;
}

void ABaseChangeableActor::ChangeCurrentMesh(WorldModes Mode)
{
	if (!bIsMeshChangeable) return;
	Super::ChangeCurrentMesh(Mode);
}

bool ABaseChangeableActor::GetMeshChangeable() const
{
	return bIsMeshChangeable;
}