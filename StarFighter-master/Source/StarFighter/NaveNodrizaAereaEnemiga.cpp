// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveNodrizaAereaEnemiga.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Proyectil_Bala.h"

// Sets default values
ANaveNodrizaAereaEnemiga::ANaveNodrizaAereaEnemiga()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveNodrizaMesh(TEXT("/Game/Meshes/Nave_3D.Nave_3D"));
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NaveNodriza = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nave Nodriza"));
	RootComponent = NaveNodriza;
	NaveNodriza->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	NaveNodriza->SetStaticMesh(NaveNodrizaMesh.Object);

	TArray<AActor*>Instances;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANaveNodrizaAereaEnemiga::StaticClass(), Instances);
	if (Instances.Num() > 1)
	{
		Instance = Cast<ANaveNodrizaAereaEnemiga>(Instances[0]);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("%s ya existe"), *Instance->GetName()));
		Destroy();
	}

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);

}

// Called when the game starts or when spawned
void ANaveNodrizaAereaEnemiga::BeginPlay()
{
	Super::BeginPlay();

	TotalTime = 60.0f;

	TimeSinceLastShot = 0.0f;

	Size = 3.0f;
	this->SetActorScale3D(FVector(Size, Size, Size));

	RandomStart = FMath::Rand();
	
}

// Called every frame
void ANaveNodrizaAereaEnemiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	//Current_Location.X += FMath::Sin(TotalTime + RandomStart);
	Current_Location.X -= 1.0f;
	//Current_Rotation.Pitch += 1.0f;

	this->SetActorLocation(Current_Location - (Current_Velocity * DeltaTime));
	//this->SetActorRotation(Current_Rotation);

	//handle shooting
	
	TotalTime += DeltaTime;

	TimeSinceLastShot+= DeltaTime;
	fBurstDelay += DeltaTime;

	Disparo += DeltaTime;

	if (TimeSinceLastShot >= 1.0f && !bHit && fBurstDelay >= 0.05f)
	{
		const FVector FireDirection = FVector(-1.0f, 0.0f, 0.f).GetClampedToMaxSize(1.0f);
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		if (Disparo < 10) {
			Disparo += 1;
			GetWorld()->SpawnActor<AProyectil_Bala>(SpawnLocation, FireRotation);
			GetWorld()->SpawnActor<AProyectil_Bala>(SpawnLocation + 50.0f, FireRotation);
			GetWorld()->SpawnActor<AProyectil_Bala>(SpawnLocation + 100.0f, FireRotation);
			GetWorld()->SpawnActor<AProyectil_Bala>(SpawnLocation - 50.0f, FireRotation);
			GetWorld()->SpawnActor<AProyectil_Bala>(SpawnLocation - 100.0f, FireRotation);

			UE_LOG(LogTemp, Warning, TEXT("Disparo"));
			fBurstDelay = 0.0f;
			TimeSinceLastShot = 0.0f;

		}
	}
}

// Called to bind functionality to input
void ANaveNodrizaAereaEnemiga::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
