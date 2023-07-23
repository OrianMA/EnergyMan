// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainCharacter.h"

// Sets default values
ACPP_MainCharacter::ACPP_MainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_MainCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocationAndRotation(NewLocation, NewRotation, false, 0, ETeleportType::None);
}

void ACPP_MainCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACPP_MainCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ACPP_MainCharacter::Jump()
{
	bPressedJump = true;
}

void ACPP_MainCharacter::StopJumping()
{
	bPressedJump = false;
}

void ACPP_MainCharacter::Interact()
{
	isInteract = true;
}

void ACPP_MainCharacter::StopInteract() 
{
	isInteract = false;
}

void ACPP_MainCharacter::LookAround(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ACPP_MainCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

// Called every frame
void ACPP_MainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPP_MainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACPP_MainCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACPP_MainCharacter::MoveRight);
	InputComponent->BindAxis("MouseY", this, &ACPP_MainCharacter::LookUp);
	InputComponent->BindAxis("MouseX", this, &ACPP_MainCharacter::LookAround);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_MainCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACPP_MainCharacter::StopJumping);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ACPP_MainCharacter::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &ACPP_MainCharacter::StopInteract);

	
}