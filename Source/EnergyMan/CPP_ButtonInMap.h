// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CPP_StatsPanelInMan.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_ButtonInMap.generated.h"

UCLASS()
class ENERGYMAN_API ACPP_ButtonInMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_ButtonInMap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "public variables")
		class AEnergyBall* currentEnergyBall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "public variables")
		float ValueToIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "public variables")
		float ValueToDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "public variables")
		bool IsIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		class UStaticMeshComponent* MeshToChangeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		UMaterial* ButtonMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		UMaterialInstanceDynamic* dynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		FLinearColor ColorInDisable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		FLinearColor ColorInHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		FLinearColor ColorInEnable;

	//In cpp class
	class ACPP_MainCharacter* currentCharacter;
	FTimerHandle Handle;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Sphere")
		class USphereComponent* CollisionSphere;

	//UPROPERTY(VisibleAnywhere)
	//	class UBoxComponent* TriggerVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
