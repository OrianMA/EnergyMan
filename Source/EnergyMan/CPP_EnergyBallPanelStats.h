// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_EnergyBallPanelStats.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYMAN_API UCPP_EnergyBallPanelStats : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		class UTextBlock* MinJouleText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		class UTextBlock* MaxJouleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		class UTextBlock* MinTempText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Min and Max")
		class UTextBlock* MaxTempText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentStats")
		class UTextBlock* CurrentJouleText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentStats")
		class UTextBlock* CurrentTempText;

	// Called every frame
	//virtual void Tick(float DeltaTime) override;




public:

	void ChangeText(FName name, float value);
	void ChangeText(FName name, FText text);

	
};
