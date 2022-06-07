// Fill out your copyright notice in the Description page of Project Settings.


#include "Torretas.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Sets default values
ATorretas::ATorretas()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh(TEXT("/Game/Meshes/Nave_3D.Nave_3D"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TorretaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torreta"));
	RootComponent = TorretaMesh;
	TorretaMesh->SetStaticMesh(TurretMesh.Object);

}

// Called when the game starts or when spawned
void ATorretas::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorretas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATorretas::SetSoporteTorreta(FString mySoporteTorreta)
{
	SoporteTorreta = mySoporteTorreta;
}

void ATorretas::SetCuerpoTorreta(FString myCuerpoTorreta)
{
	CuerpoTorreta = myCuerpoTorreta;
}

void ATorretas::SetArmasTorreta(FString myArmasTorreta)
{
	ArmasTorreta = myArmasTorreta;
}

void ATorretas::TorretasCharacteristics()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("%s"), *SoporteTorreta));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("%s"), *CuerpoTorreta));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("%s"), *ArmasTorreta));

}

