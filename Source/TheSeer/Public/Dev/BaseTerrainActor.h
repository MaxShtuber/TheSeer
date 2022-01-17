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

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ChangeCurrentMesh(WorldModes Mode);

private:
	TMap <WorldModes, UStaticMeshComponent*> Meshes;
	UStaticMeshComponent* CurrentMesh = nullptr;
	bool bIsMeshChangeable = false;

	void TurnOffMesh(UStaticMeshComponent* Mesh);
	void TurnOnMesh(UStaticMeshComponent* Mesh);

};
