// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextBlock.h"
#include "CPP_EnergyBallPanelStats.h"

void UCPP_EnergyBallPanelStats::ChangeText(FName name, float value)
{	
	UTextBlock* tempTextBlock = Cast<UTextBlock>(GetWidgetFromName(name));

	if (tempTextBlock) {
		tempTextBlock->SetText(FText::AsNumber(value));
		
	}
	else {
		FString MyMessage = TEXT("Pas trouve");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyMessage);
	}
}

void UCPP_EnergyBallPanelStats::ChangeText(FName name, FText text)
{
	UTextBlock* tempTextBlock = Cast<UTextBlock>(GetWidgetFromName(name));

	if (tempTextBlock) {
		tempTextBlock->SetText(text);

	}
	else {
		FString MyMessage = TEXT("Pas trouve");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyMessage);
	}
}
//void UCPP_EnergyBallPanelStats::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//
//}
