// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameModeBase.h"
#include "BaseTerrainActor.generated.h"

UCLASS()
class THESEER_API ABaseTerrainActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseTerrainActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* FirstWorldMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* SecondWorldMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* ThirdWorldMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;

	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void ChangeCurrentMesh(WorldModes Mode);

	UStaticMeshComponent* GetCurrentMesh() const
	{
		return CurrentMesh;
	}

	TMap<WorldModes, UStaticMeshComponent*> GetMeshes() const
	{
		return Meshes;
	}

	void virtual TurnOffMesh(UStaticMeshComponent* Mesh);
	void virtual TurnOnMesh(UStaticMeshComponent* Mesh);
	void SetCurrentMesh(UStaticMeshComponent* Mesh)
	{
		CurrentMesh = Mesh;
	}
  
private:
	TMap <WorldModes, UStaticMeshComponent*> Meshes;
	UStaticMeshComponent* CurrentMesh = nullptr;
	bool bIsMeshChangeable = false;

};
