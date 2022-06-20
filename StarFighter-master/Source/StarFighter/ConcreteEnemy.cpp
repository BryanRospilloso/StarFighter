// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcreteEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Sets default values
AConcreteEnemy::AConcreteEnemy()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CEnemyMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConcreteEnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Concrete Enemy Mesh"));
	RootComponent = ConcreteEnemyMesh;
	//CapsulaArmaMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ConcreteEnemyMesh->SetStaticMesh(CEnemyMesh.Object);

}

// Called when the game starts or when spawned
void AConcreteEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConcreteEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

