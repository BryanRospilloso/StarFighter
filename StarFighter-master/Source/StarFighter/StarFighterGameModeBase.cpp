// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveNodrizaAereaEnemiga.h"
#include "Builder_Main.h"
#include "GeneradorCapsulasArmas.h"
#include "GeneradorCapsulasEnergia.h"
#include "ConcreteEnemy.h"
#include "MeleeEnemy.h"
#include "ProjectileEnemy.h"

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();
	//UE_LOG(LogTemp, Warning, TEXT("Dentro de BeginPlay en GameModeBase"));
	GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(FVector(-10.0f, -9.0f, 300.0f), FRotator(0.0f, 90.0f, 0.0f));
	GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(FVector(-20.0f, -9.0f, 200.0f), FRotator(0.0f, 180.0f, 0.0f));
	GetWorld()->SpawnActor<ABuilder_Main>(FVector(-400.0f, 580.0f, 80.0f), FRotator::ZeroRotator);

	//Spawn a Concrete Enemy
	AConcreteEnemy* ConcreteEnemy = GetWorld()->SpawnActor<AConcreteEnemy>(FVector(-400.0f, 580.0f, 100.0f), FRotator(0.0f, 180.0f, 0.0f));

	//Spawn a Melee Enemy and set its Enemy to the Concrete one 
	AMeleeEnemy* MeleeEnemy = GetWorld()->SpawnActor<AMeleeEnemy>(AMeleeEnemy::StaticClass());
	MeleeEnemy->SetEnemy(ConcreteEnemy);

	//Spawn a Projectile Enemy and set its Enemy to the Melee one
	AProjectileEnemy* ProjectileEnemy = GetWorld()->SpawnActor<AProjectileEnemy>(AProjectileEnemy::StaticClass());
	ProjectileEnemy->SetEnemy(MeleeEnemy);

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Melee Enemies are on the horizon"));
	Enemy = MeleeEnemy;
	Enemy->Fight();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Melee Enemies cause %i damage"), Enemy->GetDamage()));
	Enemy->Die();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Enemies are now armed with guns"));
	Enemy = ProjectileEnemy;
	Enemy->Fight();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Projectile Enemies cause %i damage"), Enemy->GetDamage()));
	Enemy->Die();

}

void AStarFighterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float ProbabilidadAparicionCapsula = FMath::RandRange(1, 80);
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Dentro de Tick")));
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, FString::Printf(TEXT("Capsula generada %f"), ProbabilidadAparicionCapsula));

	if (ProbabilidadAparicionCapsula == 1.0f) {

		//Create the Shops
		AGeneradorCapsulas* GeneradorCapsulaArma = GetWorld()->SpawnActor<AGeneradorCapsulasArmas>(AGeneradorCapsulasArmas::StaticClass());
		ACapsula* Capsula = GeneradorCapsulaArma->GetCapsula("Arma1");
		
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Silver, FString::Printf(TEXT("Capsula generada %s"), *Capsula->GetNombre()));

	}
	else if (ProbabilidadAparicionCapsula == 20.0f) {

		//Create the Shops
		AGeneradorCapsulas* GeneradorCapsulaArma = GetWorld()->SpawnActor<AGeneradorCapsulasArmas>(AGeneradorCapsulasArmas::StaticClass());
		ACapsula* Capsula = GeneradorCapsulaArma->GetCapsula("Escudo1");
		
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Capsula generada %s"), *Capsula->GetNombre()));

	}
	else if (ProbabilidadAparicionCapsula == 40.0f) {

		//Create the Shops
		AGeneradorCapsulas* GeneradorCapsulaArma = GetWorld()->SpawnActor<AGeneradorCapsulasEnergia>(AGeneradorCapsulasEnergia::StaticClass());
		ACapsula* Capsula = GeneradorCapsulaArma->GetCapsula("Energia1");
		
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Capsula generada %s"), *Capsula->GetNombre()));

	}
	else if (ProbabilidadAparicionCapsula == 60.0f) {

		//Create the Shops
		AGeneradorCapsulas* GeneradorCapsula = GetWorld()->SpawnActor<AGeneradorCapsulasEnergia>(AGeneradorCapsulasEnergia::StaticClass());
		ACapsula* Capsula = GeneradorCapsula->GetCapsula("Vida1");
		
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Capsula generada %s"), *Capsula->GetNombre()));

	}
}
