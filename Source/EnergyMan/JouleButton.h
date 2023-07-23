// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_ButtonInMap.h"
#include "JouleButton.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYMAN_API AJouleButton : public ACPP_ButtonInMap
{
	GENERATED_BODY()


public:


	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	void DetectAndActiveButton();

};
