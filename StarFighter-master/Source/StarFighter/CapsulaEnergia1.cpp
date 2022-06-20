// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulaEnergia1.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "NaveAereaJugador.h"

ACapsulaEnergia1::ACapsulaEnergia1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsulaEnergia1Mesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsulaEnergiaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Capsula Energia"));
	RootComponent = CapsulaEnergiaMesh;
	//CapsulaArmaMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsulaEnergiaMesh->SetStaticMesh(CapsulaEnergia1Mesh.Object);
}

// Called when the game starts or when spawned
void ACapsulaEnergia1::BeginPlay()
{
	Super::BeginPlay();

	Nombre = "Capsula Energia 1";
	TipoCapsula = "Capsula que sube al maximo el nivel de energia";
	TipoEfecto = "Incrementa al tope la energia en ese momento";
	TipoDuracion = "Mientras el jugador este vivo";
	TiempoDuracion = 10.0f;

	size = 0.5;
	this->SetActorScale3D(FVector(size, size, size));
}

void ACapsulaEnergia1::Generar()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("Generando una capsula de Energia1"));
}

void ACapsulaEnergia1::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ANaveAereaJugador* CEnergia1 = Cast<ANaveAereaJugador>(Other);
	CEnergia1->CollectableCapsulaEnergia1();
	this->Destroy();
}
