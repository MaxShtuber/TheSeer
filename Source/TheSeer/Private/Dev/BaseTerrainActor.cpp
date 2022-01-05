// 10.8 Team. All rights reserved.

#include "Dev/BaseTerrainActor.h"

ABaseTerrainActor::ABaseTerrainActor()
{
	PrimaryActorTick.bCanEverTick = false;

	FirstWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("FirstWorldMesh");
	SetRootComponent(FirstWorldMesh);
	SecondWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("SecondWorldMesh");
	SecondWorldMesh->SetupAttachment(FirstWorldMesh);
	ThirdWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("ThirdWorldMesh");
	ThirdWorldMesh->SetupAttachment(FirstWorldMesh);
	FourthWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("FourthWorldMesh");
	FourthWorldMesh->SetupAttachment(FirstWorldMesh);
	FifthWorldMesh = CreateDefaultSubobject<UStaticMeshComponent>("FifthWorldMesh");
	FifthWorldMesh->SetupAttachment(FirstWorldMesh);
	Meshes.Add(WorldModes::FirstWorld, FirstWorldMesh);
	Meshes.Add(WorldModes::SecondWorld, SecondWorldMesh);
	Meshes.Add(WorldModes::ThirdWorld, ThirdWorldMesh);
	Meshes.Add(WorldModes::FourthWorld, FourthWorldMesh);
	Meshes.Add(WorldModes::FifthWorld, FifthWorldMesh);

}

void ABaseTerrainActor::BeginPlay()
{
	Super::BeginPlay();

	for (auto Mesh : Meshes)
	{
		if (!CurrentMesh)
		{
			CurrentMesh = Mesh.Value;
			continue;
		}
		TurnOffMesh(Mesh.Value);
	}

	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnChangeWorldMode.AddUObject(this, &ABaseTerrainActor::ChangeCurrentMesh);
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