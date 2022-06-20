// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulaArma1.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "NaveAereaJugador.h"

ACapsulaArma1::ACapsulaArma1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsulaArma1Mesh(TEXT("/Game/Meshes/defaultpickup.defaultpickup"));

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsulaArmaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Capsula Arma"));
	RootComponent = CapsulaArmaMesh;
	//CapsulaArmaMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsulaArmaMesh->SetStaticMesh(CapsulaArma1Mesh.Object);
}

// Called when the game starts or when spawned
void ACapsulaArma1::BeginPlay()
{
	Super::BeginPlay();

	Nombre = "Capsula Arma 1";
	TipoCapsula = "Capsula de aumento de danio";
	TipoEfecto = "Incrementa el danio de las balas disparadas";
	TipoDuracion = "Mientra este activo";
	TiempoDuracion = 10.0f;

	size = 0.3;
	this->SetActorScale3D(FVector(size, size, size));

}

void ACapsulaArma1::Generar()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Silver, TEXT("Generando una capsula de Arma1"));
}

void ACapsulaArma1::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ANaveAereaJugador* CArma1 = Cast<ANaveAereaJugador>(Other);
	CArma1->CollectableCapsulaArma1();
	this->Destroy();
}

