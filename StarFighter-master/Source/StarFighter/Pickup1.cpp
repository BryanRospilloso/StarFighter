// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup1.h"
#include "NaveAereaJugador.h"

// Sets default values
APickup1::APickup1()
{
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> Pickup1Mesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PickUp1Mesh->SetStaticMesh(Pickup1Mesh.Object);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PickUp1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp1Mesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	PickUp1Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void APickup1::BeginPlay()
{
	Super::BeginPlay();

	bHit = false;

	OnActorBeginOverlap.AddDynamic(this, &APickup1::OnBeginOverlap);
	
}

// Called every frame
void APickup1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = this->GetActorLocation();
	NewLocation.X -= DeltaTime * 50.0f;
	NewLocation.Z = 0;
	this->SetActorLocation(NewLocation);

	if (bHit)
	{
		this->Destroy();
	}

}

void APickup1::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ANaveAereaJugador* Pickup1 = Cast<ANaveAereaJugador>(Other);
	Pickup1->CollectablePickup1();
	this->Destroy();

}

void APickup1::OnBeginOverlap(AActor* Pickup1Actor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Wall1") || OtherActor->ActorHasTag("Wall2") || OtherActor->ActorHasTag("Wall3") || OtherActor->ActorHasTag("Wall4"))
	{
		bHit = true;
	}
		

}
