// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_MainCharacter.generated.h"

UCLASS()
class ENERGYMAN_API ACPP_MainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MainCharacter();

	UPROPERTY(EditAnywhere, Category = Location)
		FVector NewLocation;

	UPROPERTY(EditAnywhere, Category = Location)
		FQuat NewRotation;

	bool isInteract;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Jump();
	void StopJumping();
	void Interact();
	void StopInteract();
	void LookAround(float AxisValue);
	void LookUp(float AxisValue);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
