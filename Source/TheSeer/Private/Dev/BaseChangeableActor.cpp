// 10.8 Team. All rights reserved.

#include "Dev/BaseChangeableActor.h"
#include "Components/TextRenderComponent.h"

ABaseChangeableActor::ABaseChangeableActor()
{
	auto RootComponent_ = StaticCast<UStaticMeshComponent*>(GetRootComponent());
	RootComponent_->SetMobility(EComponentMobility::Movable);
	OutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>("OutlineMesh");
	OutlineMesh->SetupAttachment(GetRootComponent());
	OutlineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OutlineMesh->SetVisibility(false);
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	TextComponent->SetupAttachment(GetRootComponent());
}

void ABaseChangeableActor::BeginPlay()
{
	Super::BeginPlay();
	auto RootComponent_ = StaticCast<UStaticMeshComponent*>(GetRootComponent());
	RootComponent_->SetMobility(EComponentMobility::Movable);
	TextComponent->SetText(ActivateDescription);
	TextComponent->SetVisibility(false);
}

void ABaseChangeableActor::SetMeshChangeable(bool NewMeshChangeable)
{
	bIsMeshChangeable = NewMeshChangeable;
}

void ABaseChangeableActor::EnableCurrentMeshPhysics() const
{
	auto RootComponent_ = StaticCast<UStaticMeshComponent*>(GetRootComponent());
	if(IsValid(RootComponent_))
	{
		for (auto Mesh: GetMeshes())
		{
			Mesh.Value->SetActive(false);
		}
		RootComponent_->SetStaticMesh(GetCurrentMesh()->GetStaticMesh());
		RootComponent_->SetSimulatePhysics(true);
		RootComponent_->SetVisibility(true);

	}
}

void ABaseChangeableActor::DisableCurrentMeshPhysics()
{
	auto RootComponent_ = StaticCast<UStaticMeshComponent*>(GetRootComponent());
	if(IsValid(RootComponent_))
	{
		RootComponent_->SetSimulatePhysics(false);
		RootComponent_->SetVisibility(false);
		for (auto Mesh: GetMeshes())
		{
			Mesh.Value->SetActive(true);
		}
	}
}

void ABaseChangeableActor::TurnOnMesh(UStaticMeshComponent* Mesh)
{
	Super::TurnOnMesh(Mesh);
	OutlineMesh->SetStaticMesh(Mesh->GetStaticMesh());
	OutlineMesh->SetWorldScale3D(GetActorScale3D());
	for (int index = 0; index < OutlineMesh->GetNumMaterials(); index++)
	{
		OutlineMesh->SetMaterial(index, OutlineMaterial);
	};
}

void ABaseChangeableActor::TurnOffMesh(UStaticMeshComponent* Mesh)
{
	Super::TurnOffMesh(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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