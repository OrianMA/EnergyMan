// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ButtonInMap.h"



// Sets default values
ACPP_ButtonInMap::ACPP_ButtonInMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->SetSphereRadius(90.0f);
	//CollisionSphere->bGenerateOverlapEvents = true;
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionSphere->bHiddenInGame = false;
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACPP_ButtonInMap::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ACPP_ButtonInMap::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACPP_ButtonInMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_ButtonInMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_ButtonInMap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ACPP_ButtonInMap::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}





