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
	UStaticMeshComponent* FourthWorldMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* FifthWorldMesh;

	virtual void BeginPlay() override;

private:
	TMap <WorldModes, UStaticMeshComponent*> Meshes;
	UStaticMeshComponent* CurrentMesh = nullptr;

	void TurnOffMesh(UStaticMeshComponent* Mesh);
	void TurnOnMesh(UStaticMeshComponent* Mesh);

	UFUNCTION()
	void ChangeCurrentMesh(WorldModes Mode);
};
