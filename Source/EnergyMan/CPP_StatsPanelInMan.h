// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_StatsPanelInMan.generated.h"

UCLASS()
class ENERGYMAN_API ACPP_StatsPanelInMan : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_StatsPanelInMan();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
		class UWidgetComponent* CurrentPanelStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
		class AEnergyBall* CurrentEnergyBall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateUIText(FName nameText, float value);
	void UpdateUIText(FName nameText, FText text);

};
