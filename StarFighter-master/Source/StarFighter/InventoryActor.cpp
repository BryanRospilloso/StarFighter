// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActor.h"
#include "Time.h"

// Sets default values
AInventoryActor::AInventoryActor():Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();

	bHit = false;

	OnActorBeginOverlap.AddDynamic(this, &AInventoryActor::OnBeginOverLap);

}

// Called every frame
void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	srand(time(NULL));

	float rand1 = rand() % 50 - 20;
	float rand2 = rand() % 50 - 20;

	MoveSpeed = 150.0f;

	const FVector Move = FVector(-2.0f, rand2, 0.0f).GetClampedToMaxSize(1.0f);
	const FVector Movement = Move * MoveSpeed * DeltaTime;

	if (Movement.SizeSquared() > 1.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

	}

	if (bHit)
	{
		this->Destroy();
	}


}

void AInventoryActor::PickUp()
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AInventoryActor::PutDown(FTransform TargetLocation)
{
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorLocation(TargetLocation.GetLocation());
}

void AInventoryActor::OnBeginOverLap(AActor* OneActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Wall1") || OtherActor->ActorHasTag("Wall2") || OtherActor->ActorHasTag("Wall3") || OtherActor->ActorHasTag("Wall4"))
	{
		bHit = true;
	}

}

