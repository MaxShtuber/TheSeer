// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGameModeBase.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ABaseChangeableActor;
class UNiagaraComponent;

DECLARE_DELEGATE_OneParam(FInputSwitchWorldModeSignature, WorldModes);
DECLARE_MULTICAST_DELEGATE(FOnJournalOpenSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnableToChangeWorldSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnJournalSetPageSignature, int);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectTake);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectDrop);

UCLASS()
class THESEER_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

	FOnJournalOpenSignature OnJournalOpen;
	FOnJournalSetPageSignature OnJournalSetPage;

	UPROPERTY(BlueprintAssignable)
	FOnUnableToChangeWorldSignature UnableToChangeWorld;

	UPROPERTY(BlueprintAssignable)
	FOnObjectTake OnObjectTake;
	UPROPERTY(BlueprintAssignable)
	FOnObjectDrop OnObjectDrop;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 300;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 600;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	AActor* Checkpoint;

	UFUNCTION(BlueprintCallable)
	void EnableChangeWorld();
	UFUNCTION(BlueprintCallable)
	void DisableChangeWorld();

	UPROPERTY(BlueprintReadWrite)
	ABaseChangeableActor* CurrentTakenActor = nullptr;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* ChangeWorldEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer")
	float SetWorldTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object")
	float RangeOfTakenObject = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object")
	FName AttachObjectSocketName = TEXT("AttachObjectSocket");

	virtual void BeginPlay() override;
	
private:
	FVector InitialTakenObjectScale;
	bool bWantsToInteract = false;
	bool bCanSetWorld = true;
	bool bRestrictSetWorld = false;
	TArray<ABaseChangeableActor*> OverlapedActors;
	
	FTimerHandle SetWorldTimerHandler;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartInteract();
	void StartSprint();
	void StopSprint();
	void PauseGame();
	void TakeObject();
	void DropObject();
	void OnOpenJournal();

	UFUNCTION()
	void SetWorldMode(WorldModes Mode);

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ChangeSetWorld();
};
