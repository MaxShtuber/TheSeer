// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dev/BaseTerrainActor.h"
#include "BasePageActor.generated.h"

/**
 * 
 */
UCLASS()
class THESEER_API ABasePageActor : public ABaseTerrainActor
{
	GENERATED_BODY()
public:
	void OnStartInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	USoundBase* PickUpSound;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pages")
	int PageNumber = 0;
};
