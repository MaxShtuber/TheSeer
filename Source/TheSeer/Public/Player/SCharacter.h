// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGameModeBase.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class ABaseChangeableActor;

DECLARE_DELEGATE_OneParam(FInputSwitchWorldModeSignature, WorldModes);

UCLASS()
class THESEER_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer")
	float SetWorldTime = 3.0f;

	virtual void BeginPlay() override;

private:
	bool bWantsToInteract = false;
	bool bCanSetWorld = true;
	TArray<ABaseChangeableActor*> OverlapedActors;
	FTimerHandle SetWorldTimerHandler;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartInteract();
	void PauseGame();

	UFUNCTION()
	void SetWorldMode(WorldModes Mode);

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ChangeSetWorld();
};
