// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dev/BaseTerrainActor.h"
#include "QuestPlaceActor.generated.h"

/**
 * 
 */
UCLASS()
class THESEER_API AQuestPlaceActor : public ABaseTerrainActor
{
	GENERATED_BODY()
public:
	AQuestPlaceActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag")
	int32 TagItem = 0;

	void SetChangeableActorPlacedInside(bool NewValue);
	void OnStartInteract();
	bool CanInteract() const { return !bIsChangeableActorPlacedInside; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* SignalMesh;

	virtual void BeginPlay() override;
	virtual void ChangeCurrentMesh(WorldModes Mode) override;
private:
	bool bIsChangeableActorPlacedInside = false;
};
