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
	FText ActivateDescription = FText::FromString(TEXT("Press E to stabilize this object"));

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Text")
	FText DeactivateDescription = FText::FromString(TEXT("Object stabilized. Press E to destabilize"));

protected:

	void ChangeCurrentMesh(WorldModes Mode) override;

	virtual void BeginPlay() override;

private:
	bool bIsMeshChangeable = true;
};
