// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonTemperature.h"
#include "CPP_MainCharacter.h"
#include "EnergyBall.h"

void AButtonTemperature::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//MyDynamicMaterial = (UMaterialInstanceDynamic*)MyBaseMaterial;

	currentCharacter = Cast<ACPP_MainCharacter>(OtherActor);
	if (currentCharacter != NULL) {
		//MyDynamicMaterial->SetVectorParameterValue("Color", colorInHold);
		//MeshToChangeMaterial->SetMaterial(0, ButtonMaterialWhenHold);
		GetWorldTimerManager().SetTimer(Handle, this, &AButtonTemperature::DetectAndActiveButton, 0.3f, true, .2f);
	}
}

void AButtonTemperature::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	currentCharacter = Cast<ACPP_MainCharacter>(OtherActor);
	if (currentCharacter != NULL) {

		GetWorldTimerManager().ClearTimer(Handle);
		//ButtonMaterial->SetVectorParameterValueEditorOnly("Color", ColorInDisable);
		//MeshToChangeMaterial->SetMaterial(0, ButtonMaterial);
		//cubeMaterial->SetVectorParameterValue("Color", colorInDisable);
	}
}

void AButtonTemperature::DetectAndActiveButton()
{
	if (currentCharacter->isInteract) {
		//ButtonMaterial->SetVectorParameterValueEditorOnly("Color", ColorInEnable);
		//cubeMaterial->SetVectorParameterValue("Color", ColorInEnable);
		//MeshToChangeMaterial->SetMaterial(0, ButtonMaterialWhenEnable);

		if (IsIncrease) {
			currentEnergyBall->IncrementTemperature(ValueToIncrease);
		}
		else {
			currentEnergyBall->DecrementTemperature(ValueToDecrease);
		}
	}
	else {
		//ButtonMaterial->SetVectorParameterValueEditorOnly("Color", ColorInHold);
	}
}
