// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulaVida1.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "NaveAereaJugador.h"

ACapsulaVida1::ACapsulaVida1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsulaVida1Mesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsulaVidaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Capsula Vida"));
	RootComponent = CapsulaVidaMesh;
	//CapsulaArmaMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsulaVidaMesh->SetStaticMesh(CapsulaVida1Mesh.Object);
}

// Called when the game starts or when spawned
void ACapsulaVida1::BeginPlay()
{
	Super::BeginPlay();

	Nombre = "Capsula Vida 1";
	TipoCapsula = "Capsula que recupera vida";
	TipoEfecto = "Permite curar el daño y recuperar la vida del jugador en caso fuera daniado";
	TipoDuracion = "Se aplica instantaneamente, dura hasta que el jugador sea daniado nuevamente";
	TiempoDuracion = 10.0f;

	size = 2.0;
	this->SetActorScale3D(FVector(size, size, size));
}

void ACapsulaVida1::Generar()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Generando una capsula de Vida1"));
}

void ACapsulaVida1::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ANaveAereaJugador* CVida1 = Cast<ANaveAereaJugador>(Other);
	CVida1->CollectableCapsulaVida1();
	this->Destroy();
}
