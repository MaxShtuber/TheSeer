// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dev/BaseTerrainActor.h"
#include "BaseChangeableActor.generated.h"

class UTextRenderComponent;

/**
 * 
 */
UCLASS()
class THESEER_API ABaseChangeableActor : public ABaseTerrainActor
{
	GENERATED_BODY()
public:
	ABaseChangeableActor();

	void SetMeshChangeable(bool NewMeshChangeable);
	bool GetMeshChangeable() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* TextComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Text")
	FText ActivateDescription = FText::FromString(TEXT("Press E to pick object"));

	void EnableCurrentMeshPhysics() const;

	
	void DisableCurrentMeshPhysics();

protected:

	UFUNCTION()
	void DisableCurrentMeshPhysicsCallback(UPrimitiveComponent* Comp, FName BoneName)
	{
		DisableCurrentMeshPhysics();
	}
	
	void ChangeCurrentMesh(WorldModes Mode) override;

	virtual void BeginPlay() override;

private:
	bool bIsMeshChangeable = true;
};
