// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameModeBase.h"
#include "BaseRuneActor.generated.h"

UCLASS()
class THESEER_API ABaseRuneActor : public AActor
{
	GENERATED_BODY()
public:
	ABaseRuneActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStartInteract();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* RuneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag")
	WorldModes RuneTag;
};
