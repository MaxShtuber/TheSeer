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

	for (auto mesh : GetMeshes())
	{
		mesh.Value->BodyInstance.bGenerateWakeEvents = true;
		mesh.Value->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		mesh.Value->OnComponentSleep.AddDynamic(
			this, &ABaseChangeableActor::ABaseChangeableActor::DisableCurrentMeshPhysicsCallback);
	}

	TextComponent->SetText(ActivateDescription);
	TextComponent->SetVisibility(false);
}

void ABaseChangeableActor::SetMeshChangeable(bool NewMeshChangeable)
{
	bIsMeshChangeable = NewMeshChangeable;
}

void ABaseChangeableActor::EnableCurrentMeshPhysics() const
{
	if(IsValid(GetCurrentMesh()))
	{
		GetCurrentMesh()->SetSimulatePhysics(true);
	}
}

void ABaseChangeableActor::DisableCurrentMeshPhysics()
{
	if(IsValid(GetCurrentMesh()))
	{
		GetCurrentMesh()->SetSimulatePhysics(false);
	}
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