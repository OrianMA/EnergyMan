// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CPP_StatsPanelInMan.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnergyBall.generated.h"

UCLASS()
class ENERGYMAN_API AEnergyBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnergyBall();

	//Editor variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "public variables")
	float CurrentJoule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "public variables")
	float CurrentTemperature;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SphereMeshComponent;

	// Le matériau parent que vous souhaitez utiliser comme base pour le Material Instance Dynamic.
	UPROPERTY(EditAnywhere, Category = "Material")
		UMaterial* ParentMaterial;

	// Le Material Instance Dynamic que nous allons créer et appliquer à la sphère.
	UPROPERTY()
		UMaterialInstanceDynamic* DynamicMaterialInstance;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		float minJoule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		float maxJoule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		float minTemp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		float maxTemp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Proprety")
		float minValueExpodential = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Proprety")
		float ExponentialStrength = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Proprety")
		float currentJouleIntesity;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Proprety")
		FLinearColor BaseColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Proprety")
		float ExponentialStrengthColor;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joule and Temp variation")
		float delayBetweenVariation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joule and Temp variation")
		int SpeedJouleVariation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joule and Temp variation")
		float SpeedTempVariation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		ACPP_StatsPanelInMan* panelStats;


	bool isDestroy;

	float distance;
	float intensity;


private:

	FTimerHandle Handle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void IncrementJoule(int jouleToUpdate);
	void DecrementJoule(int jouleToUpdate);

	void IncrementTemperature(float temperatureToIncrease);
	void DecrementTemperature(float temperatureToDecrease);

	void IncrementDecrementInTime();

	void DestroyBall();

	FLinearColor ExponentialColorChange(FLinearColor _BaseColor, float _ExponentialStrength, float Progress);

};
