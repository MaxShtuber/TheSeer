// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dev/BaseTerrainActor.h"
#include "QuestPlaceActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartInteractSignature);

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

	
	UPROPERTY(BlueprintAssignable, Category="Rama Melee Weapon")
	FOnStartInteractSignature OnStartInteractEvent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* SignalMesh;

	virtual void BeginPlay() override;
	virtual void ChangeCurrentMesh(WorldModes Mode) override;
private:
	bool bIsChangeableActorPlacedInside = false;
};
