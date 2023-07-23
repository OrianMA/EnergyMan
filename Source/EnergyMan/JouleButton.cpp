// Fill out your copyright notice in the Description page of Project Settings.


#include "JouleButton.h"
#include "CPP_MainCharacter.h"
#include "EnergyBall.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"

void AJouleButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//MyDynamicMaterial = (UMaterialInstanceDynamic*)MyBaseMaterial;

	currentCharacter = Cast<ACPP_MainCharacter>(OtherActor);
	if (currentCharacter != NULL) {
		//MyDynamicMaterial->SetVectorParameterValue("Color", colorInHold);
		//MeshToChangeMaterial->SetMaterial(0, ButtonMaterialWhenHold);
		GetWorldTimerManager().SetTimer(Handle, this, &AJouleButton::DetectAndActiveButton, 0.3f, true, .2f);
	}
}

void AJouleButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	currentCharacter = Cast<ACPP_MainCharacter>(OtherActor);
	if (currentCharacter != NULL) {

		GetWorldTimerManager().ClearTimer(Handle);
		//ButtonMaterial->SetVectorParameterValueEditorOnly("Color", ColorInDisable);
		//MeshToChangeMaterial->SetMaterial(0, ButtonMaterial);
		//cubeMaterial->SetVectorParameterValue("Color", colorInDisable);
	}
}



void AJouleButton::DetectAndActiveButton()
{
	if (currentCharacter->isInteract) {
		//ButtonMaterial->SetVectorParameterValueEditorOnly("Color", ColorInEnable);
		//cubeMaterial->SetVectorParameterValue("Color", ColorInEnable);
		//MeshToChangeMaterial->SetMaterial(0, ButtonMaterialWhenEnable);

		if (IsIncrease) {
			currentEnergyBall->IncrementJoule(ValueToIncrease);

		}
		else {
			currentEnergyBall->DecrementJoule(ValueToDecrease);
		}
	}
	else {
		//ButtonMaterial->SetVectorParameterValueEditorOnly("Color", ColorInHold);
	}
}
