// 10.8 Team. All rights reserved.

#include "Dev/BaseTerrainActor.h"

ABaseTerrainActor::ABaseTerrainActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(Root);
	Root->SetVisibility(false);
	Root->SetMobility(EComponentMobility::Static);
	FirstWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("FirstWorldMesh");
	FirstWorldMesh->SetupAttachment(GetRootComponent());
	SecondWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("SecondWorldMesh");
	SecondWorldMesh->SetupAttachment(GetRootComponent());
	ThirdWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("ThirdWorldMesh");
	ThirdWorldMesh->SetupAttachment(GetRootComponent());
	Meshes.Add(WorldModes::FirstWorld, FirstWorldMesh);
	Meshes.Add(WorldModes::SecondWorld, SecondWorldMesh);
	Meshes.Add(WorldModes::ThirdWorld, ThirdWorldMesh);

}

void ABaseTerrainActor::BeginPlay()
{
	Super::BeginPlay();

	for (auto Mesh : Meshes)
	{
		if (!CurrentMesh)
		{
			CurrentMesh = Mesh.Value;
			TurnOnMesh(CurrentMesh);
			continue;
		}
		TurnOffMesh(Mesh.Value);
	}

	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnChangeWorldMode.AddDynamic(this, &ABaseTerrainActor::ChangeCurrentMesh);
	}
}

void ABaseTerrainActor::TurnOffMesh(UStaticMeshComponent* Mesh)
{
	Mesh->SetVisibility(false, false);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ABaseTerrainActor::TurnOnMesh(UStaticMeshComponent* Mesh)
{
	Mesh->SetVisibility(true, false);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void ABaseTerrainActor::ChangeCurrentMesh(WorldModes Mode)
{
	if (CurrentMesh)
	{
		TurnOffMesh(CurrentMesh);
	}

	CurrentMesh = *Meshes.Find(Mode);
	if (!CurrentMesh) return;

	TurnOnMesh(CurrentMesh);
}
