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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("Content/Materials/EnergySphere_Inst.uasset"));

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
			UE_LOG(LogTemp, Warning, TEXT("DynamicMaterialInstance attached successfully!"));
		}
		else
		{
			// Ajoutez un message de débogage en cas d'échec de création du DynamicMaterialInstance.
			UE_LOG(LogTemp, Error, TEXT("Failed to create DynamicMaterialInstance!"));
		}
	}else {
		UE_LOG(LogTemp, Error, TEXT("ParentMaterial is invalid!"));
	}

}

// Called when the game starts or when spawned
void AEnergyBall::BeginPlay()
{
	isDestroy = false;
	Super::BeginPlay();
	//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity", currentJouleIntesity);
	GetWorldTimerManager().SetTimer(Handle, this, &AEnergyBall::IncrementDecrementInTime, delayBetweenVariation, true, 6.0f);

	// Créez une instance de matériau dynamique à partir du matériau parent.
	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(ParentMaterial, nullptr);

	// Assurez-vous que l'instance de matériau dynamique est valide avant de l'attacher au UStaticMeshComponent.
	if (DynamicMaterialInstance)
	{
		// Attaquez le Material Instance Dynamic au UStaticMeshComponent.
		SphereMeshComponent->SetMaterial(0, DynamicMaterialInstance); // 0 est l'index du matériau que vous souhaitez remplacer.
		UE_LOG(LogTemp, Warning, TEXT("DynamicMaterialInstance attached successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create DynamicMaterialInstance!"));
	}

	SetActorHiddenInGame(true);

	distance = FMath::Abs(CurrentJoule - minValueExpodential);
	intensity = FMath::Pow(distance, ExponentialStrength);

	if (intensity < 1.0f)
	{
		intensity = 1.0f / intensity;
	}

	currentJouleIntesity = CurrentJoule * intensity;

	if (DynamicMaterialInstance)
	{
		DynamicMaterialInstance->SetScalarParameterValue("JouleIntensity", currentJouleIntesity);

		DynamicMaterialInstance->SetVectorParameterValue("ColorDiffuse", ExponentialColorChange(BaseColor, ExponentialStrengthColor, (CurrentTemperature - minTemp) / (maxTemp - minTemp)));
	}
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

		distance = FMath::Abs(CurrentJoule - minValueExpodential);
		intensity = FMath::Pow(distance, ExponentialStrength);

		if (intensity < 1.0f)
		{
			intensity = 1.0f / intensity;
		}

		currentJouleIntesity = CurrentJoule * intensity;
		//DynamicMaterialInstance->SetScalarParameterValue("JouleIntensity", currentJouleIntesity);
		//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity",  currentJouleIntesity);
		if (CurrentJoule > maxJoule) {
			DestroyBall();
		}
		else {

			if (DynamicMaterialInstance)
			{
				DynamicMaterialInstance->SetScalarParameterValue("JouleIntensity", currentJouleIntesity);

				DynamicMaterialInstance->SetVectorParameterValue("ColorDiffuse", ExponentialColorChange(BaseColor, ExponentialStrengthColor, (CurrentTemperature - minTemp) / (maxTemp - minTemp)));
			}

			if (panelStats)
				panelStats->UpdateUIText(FName("CurrentJoule"), CurrentJoule);
		}
	}
}

void AEnergyBall::DecrementJoule(int jouleToUpdate)
{	
	if (!isDestroy) {

		CurrentJoule -= jouleToUpdate;

		distance = FMath::Abs(CurrentJoule - minValueExpodential);
		intensity = FMath::Pow(distance, ExponentialStrength);

		if (intensity < 1.0f)
		{
			intensity = 1.0f / intensity;
		}

		currentJouleIntesity = CurrentJoule * intensity;

		UE_LOG(LogTemp, Error, TEXT("%f"), currentJouleIntesity);
		//energyBallMaterial->SetScalarParameterValueEditorOnly("JouleIntensity", currentJouleIntesity);

		if (CurrentJoule < minJoule) {
			DestroyBall();
		}
		else {

			if (DynamicMaterialInstance)
			{
				DynamicMaterialInstance->SetScalarParameterValue("JouleIntensity", currentJouleIntesity);

				DynamicMaterialInstance->SetVectorParameterValue("ColorDiffuse", ExponentialColorChange(BaseColor, ExponentialStrengthColor, (CurrentTemperature - minTemp) / (maxTemp - minTemp)));
			}

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
		SetActorHiddenInGame(false);
		indexDifficultyIncrease++;

		if (indexDifficultyIncrease % maxIndexDifficultyIncrease) {
			indexDifficultyIncrease = 0;
			Difficulty++;
		}

		if (CurrentJoule > (maxJoule - minJoule) / 2) {
			IncrementTemperature(SpeedTempVariation * (Difficulty * 0.4f));
		}
		else {
			DecrementTemperature(FMath::RoundToInt(SpeedTempVariation * (Difficulty * 0.4f)));
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

		panelStats->ChangeColor(FName("CurrentJoule"), FLinearColor::Red);
		panelStats->ChangeColor(FName("MinJoule"), FLinearColor::Red);
		panelStats->ChangeColor(FName("MaxJoule"), FLinearColor::Red);

		panelStats->ChangeColor(FName("CurrentTemp"), FLinearColor::Red);
		panelStats->ChangeColor(FName("MinTemp"), FLinearColor::Red);
		panelStats->ChangeColor(FName("MaxTemp"), FLinearColor::Red);
	}
}


FLinearColor AEnergyBall::ExponentialColorChange(FLinearColor _BaseColor, float _ExponentialStrength, float Progress)
{



	FLinearColor StartColor = FLinearColor::Blue; // Couleur de départ
	FLinearColor EndColor = FLinearColor::Red; // Couleur d'arrivée

	// Calculer la progression entre les deux couleurs (valeur de 0 à 1)
	//Progress = CalculateProgress(Progress, StartValue, EndValue);

	// Interpoler la couleur entre StartColor et EndColor en fonction de la progression
	return FLinearColor::LerpUsingHSV(StartColor, EndColor, Progress);



	/*// Clamp progress between 0 and 1
	Progress = FMath::Clamp(Progress, 0.0f, 1.0f);

	// Calculate the inverse progress
	float InverseProgress = 1.0f - Progress;

	// Apply exponential strength to progress and inverse progress
	float ExponentialProgress = FMath::Pow(Progress, _ExponentialStrength);
	float ExponentialInverseProgress = FMath::Pow(InverseProgress, _ExponentialStrength);

	// Interpolate the color between blue and red based on exponential progress
	FLinearColor BlueColor = FLinearColor::Blue;
	FLinearColor RedColor = FLinearColor::Red;

	FLinearColor InterpolatedColor = FLinearColor::LerpUsingHSV(BlueColor, RedColor, ExponentialProgress);

	// Combine the interpolated color with the base color using the exponential inverse progress
	FLinearColor ResultColor = FLinearColor::LerpUsingHSV(_BaseColor, InterpolatedColor, ExponentialInverseProgress);

	return ResultColor; */
}
