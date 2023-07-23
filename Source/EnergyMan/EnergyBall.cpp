// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyBall.h"

// Sets default values
AEnergyBall::AEnergyBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComponent"));
	RootComponent = SphereMeshComponent;

	// Chargez un mesh de sphère existant pour le UStaticMeshComponent.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("Engine/BasicShapes/Sphere"));

	if (SphereMeshAsset.Succeeded())
	{
		SphereMeshComponent->SetStaticMesh(SphereMeshAsset.Object);
	}

	// Assurez-vous que le matériau parent est valide.
	if (ParentMaterial)
	{
		// Créez une instance de matériau dynamique à partir du matériau parent.
		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(ParentMaterial, nullptr);

		// Assurez-vous que l'instance de matériau dynamique est valide avant de l'attacher au UStaticMeshComponent.
		if (DynamicMaterialInstance)
		{
			// Attaquez le Material Instance Dynamic au UStaticMeshComponent.
			SphereMeshComponent->SetMaterial(0, DynamicMaterialInstance); // 0 est l'index du matériau que vous souhaitez remplacer.
		}
	}

}

// Called when the game starts or when spawned
void AEnergyBall::BeginPlay()
{
	isDestroy = false;
	Super::BeginPlay();
	//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity", currentJouleIntesity);
	GetWorldTimerManager().SetTimer(Handle, this, &AEnergyBall::IncrementDecrementInTime, 0.2f, true, 2.0f);
}

// Called every frame
void AEnergyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void AEnergyBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnergyBall::IncrementJoule(int jouleToUpdate)
{
	if (!isDestroy) {
		CurrentJoule += jouleToUpdate;
		currentJouleIntesity += IntensityWhenIncrease;
		DynamicMaterialInstance->SetScalarParameterValue("JouleIntensity", currentJouleIntesity);
		//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity",  currentJouleIntesity);
		if (CurrentJoule > maxJoule) {
			DestroyBall();
		}
		else {
			if (panelStats)
				panelStats->UpdateUIText(FName("CurrentJoule"), CurrentJoule);
		}
	}
}

void AEnergyBall::DecrementJoule(int jouleToUpdate)
{	
	if (!isDestroy) {
		CurrentJoule -= jouleToUpdate;
		currentJouleIntesity -= IntensityWhenIncrease;
		//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity", currentJouleIntesity);

		if (CurrentJoule < minJoule) {
			DestroyBall();
		}
		else {
			if (panelStats)
				panelStats->UpdateUIText(FName("CurrentJoule"), CurrentJoule);
		}
	}
}

void AEnergyBall::IncrementTemperature(float temperatureToIncrease)
{
	if (!isDestroy) {
		CurrentTemperature += temperatureToIncrease;

		if (CurrentTemperature > maxTemp) {
			DestroyBall();
		}
		else {
			if (panelStats) {
				panelStats->UpdateUIText(FName("CurrentTemp"), CurrentTemperature);
			}
		}
	}
}

void AEnergyBall::DecrementTemperature(float temperatureToDecrease)
{
	if (!isDestroy) {
		CurrentTemperature -= temperatureToDecrease;
		if (CurrentTemperature < minTemp) {
			DestroyBall();
		}
		else {
			if (panelStats)
				panelStats->UpdateUIText(FName("CurrentTemp"), CurrentTemperature);
		}
	}
}

void AEnergyBall::IncrementDecrementInTime()
{
	if (!isDestroy) {
		if (CurrentJoule > (maxJoule - minJoule) / 2) {
			IncrementTemperature(SpeedTempVariation);
		}
		else {
			DecrementTemperature(SpeedTempVariation);
		}

		DecrementJoule(SpeedJouleVariation);
	}

}

void AEnergyBall::DestroyBall()
{
	//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity", 0);
	SetActorHiddenInGame(true);
	isDestroy = true;
	if (panelStats) {
		panelStats->UpdateUIText(FName("CurrentJoule"), FText::FromString("ERROR"));
		panelStats->UpdateUIText(FName("MinJoule"), FText::FromString("ERROR"));
		panelStats->UpdateUIText(FName("MaxJoule"), FText::FromString("ERROR"));

		panelStats->UpdateUIText(FName("CurrentTemp"), FText::FromString("ERROR"));
		panelStats->UpdateUIText(FName("MinTemp"), FText::FromString("ERROR"));
		panelStats->UpdateUIText(FName("MaxTemp"), FText::FromString("ERROR"));
	}
}
