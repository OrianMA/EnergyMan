// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_StatsPanelInMan.h"
#include "EnergyBall.h"
#include "Components/WidgetComponent.h"
#include "CPP_EnergyBallPanelStats.h"

// Sets default values
ACPP_StatsPanelInMan::ACPP_StatsPanelInMan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_StatsPanelInMan::BeginPlay()
{
	Super::BeginPlay();

	UpdateUIText(FName("CurrentJoule"), CurrentEnergyBall->CurrentJoule);
	UpdateUIText(FName("MinJoule"), CurrentEnergyBall->minJoule);
	UpdateUIText(FName("MaxJoule"), CurrentEnergyBall->maxJoule);

	UpdateUIText(FName("CurrentTemp"), CurrentEnergyBall->CurrentTemperature);
	UpdateUIText(FName("MinTemp"), CurrentEnergyBall->minTemp);
	UpdateUIText(FName("MaxTemp"), CurrentEnergyBall->maxTemp);



}

// Called every frame
void ACPP_StatsPanelInMan::Tick(float DeltaTime)
{
	//C'est pas le plus opti je sais :/

	Super::Tick(DeltaTime);
	

}



void ACPP_StatsPanelInMan::UpdateUIText(FName nameText, float value)
{
	UUserWidget* WidgetClass = CurrentPanelStats->GetUserWidgetObject();

	if (WidgetClass) {

		UCPP_EnergyBallPanelStats* WidgetInstance = Cast<UCPP_EnergyBallPanelStats>(WidgetClass);

		if (WidgetInstance)
		{
			WidgetInstance->ChangeText(nameText, value);
		}
	}
}

void ACPP_StatsPanelInMan::UpdateUIText(FName nameText, FText text)
{
	UUserWidget* WidgetClass = CurrentPanelStats->GetUserWidgetObject();

	if (WidgetClass) {

		UCPP_EnergyBallPanelStats* WidgetInstance = Cast<UCPP_EnergyBallPanelStats>(WidgetClass);

		if (WidgetInstance)
		{
			WidgetInstance->ChangeText(nameText, text);
		}
	}
}

void ACPP_StatsPanelInMan::ChangeColor(FName name, FLinearColor color) {

	UUserWidget* WidgetClass = CurrentPanelStats->GetUserWidgetObject();

	if (WidgetClass) {

		UCPP_EnergyBallPanelStats* WidgetInstance = Cast<UCPP_EnergyBallPanelStats>(WidgetClass);

		if (WidgetInstance)
		{
			WidgetInstance->SetColorAndOpacity(color);
		}
	}
}

