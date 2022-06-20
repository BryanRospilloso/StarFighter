// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulaEscudo1.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "NaveAereaJugador.h"

ACapsulaEscudo1::ACapsulaEscudo1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsulaEscudo1Mesh(TEXT("/Game/Meshes/Nave_3D.Nave_3D"));

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsulaEscudoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Capsula Escudo"));
	RootComponent = CapsulaEscudoMesh;
	//CapsulaArmaMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsulaEscudoMesh->SetStaticMesh(CapsulaEscudo1Mesh.Object);
}

// Called when the game starts or when spawned
void ACapsulaEscudo1::BeginPlay()
{
	Super::BeginPlay();

	Nombre = "Capsula Escudo 1";
	TipoCapsula = "Capsula de escudo";
	TipoEfecto = "Imposibilita que una municion normal dañe a la nave del jugador";
	TipoDuracion = "10 segundos";
	TiempoDuracion = 10.0f;

	size = 0.8;
	this->SetActorScale3D(FVector(size, size, size));
}

void ACapsulaEscudo1::Generar()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Generando una capsula de Escudo1"));
}

void ACapsulaEscudo1::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ANaveAereaJugador* CEscudo1 = Cast<ANaveAereaJugador>(Other);
	CEscudo1->CollectableCapsulaEscudo1();
	this->Destroy();
}
