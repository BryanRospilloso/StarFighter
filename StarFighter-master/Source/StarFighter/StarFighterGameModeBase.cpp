// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveNodrizaAereaEnemiga.h"
#include "Builder_Main.h"
#include "GeneradorCapsulasArmas.h"
#include "GeneradorCapsulasEnergia.h"
#include "ConcreteEnemy.h"
#include "MeleeEnemy.h"
#include "ProjectileEnemy.h"
#include "StarShipFacade_Main.h"
#include "ClockTower.h"
#include "FreakyAllen.h"
#include "NaveAereaEnemiga01.h"

#include "BattleShip.h"
#include "BruteForceStrategy.h"
#include "DivideConquerStrategy.h"
#include "RetreatStrategy.h"

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();
	//UE_LOG(LogTemp, Warning, TEXT("Dentro de BeginPlay en GameModeBase"));
	//GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(FVector(-10.0f, -9.0f, 300.0f), FRotator(0.0f, 90.0f, 0.0f));
	//GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(FVector(-20.0f, -9.0f, 200.0f), FRotator(0.0f, 180.0f, 0.0f));
	//GetWorld()->SpawnActor<ABuilder_Main>(FVector(-400.0f, 580.0f, 80.0f), FRotator::ZeroRotator);
	//GetWorld()->SpawnActor<AStarShipFacade_Main>(FVector::ZeroVector, FRotator::ZeroRotator);

	//Spawn a Concrete Enemy
	/*AConcreteEnemy* ConcreteEnemy = GetWorld()->SpawnActor<AConcreteEnemy>(FVector(-400.0f, 580.0f, 100.0f), FRotator(0.0f, 180.0f, 0.0f));

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
	Enemy->Die();*/

	//Spawn the Clock Tower
	//AClockTower* ClockTower = GetWorld()->SpawnActor<AClockTower>(AClockTower::StaticClass());
	//Spawn the first Subscriber and set its Clock Tower
	//GetWorld()->SpawnActor<ANaveAereaEnemiga01>(FVector(0.0f, 580.0f, 80.0f), FRotator::ZeroRotator);
	//Change the time of the Clock Tower, so the Subscribers can execute their own routine
	//ClockTower->SetTimeOfDay("Enemigo Estatico");
	//ClockTower->SetTimeOfDay("Enemigo en Movimiento");
	//ClockTower->SetTimeOfDay("Enemigo Disparando");

	//AFreakyAllen* FreakyAllen1 = GetWorld()->SpawnActor<AFreakyAllen>(AFreakyAllen::StaticClass());
	//FreakyAllen1->SetEstadoShip();

	//Enemies alert log
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		TEXT("A tiny frigate wants some trouble"));
	//Spawn the Battle Ship
	ABattleShip* BattleShip = GetWorld()->SpawnActor<ABattleShip>(ABattleShip::StaticClass());
	//Create the Brute Force Strategy and set it to the Battle Ship
	ABruteForceStrategy* BruteForceStrategy = GetWorld()->SpawnActor<ABruteForceStrategy>(ABruteForceStrategy::StaticClass());
	BattleShip->AlterManeuvers(BruteForceStrategy);
	//Engage with the current Strategy
	BattleShip->Engage();
	//Enemies alert log
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		TEXT("Four tiny frigates want some trouble"));
	//Create the Divide Conquer Strategy and set it to the Battle Ship
	ADivideConquerStrategy* DivideConquerStrategy = GetWorld()->SpawnActor<ADivideConquerStrategy>(ADivideConquerStrategy::StaticClass());
	BattleShip->AlterManeuvers(DivideConquerStrategy);
	//Engage with the current Strategy
	BattleShip->Engage();
	//Enemies alert log
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		TEXT("An aircraft carrier group wants some trouble"));
	//Create the Retreat Strategy and set it to the Battle Ship
	ARetreatStrategy* RetreatStrategy = GetWorld()->SpawnActor<ARetreatStrategy>(ARetreatStrategy::StaticClass());
	BattleShip->AlterManeuvers(RetreatStrategy);
	//Engage with the current Strategy
	BattleShip->Engage();

}

void AStarFighterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*float ProbabilidadAparicionCapsula = FMath::RandRange(1, 80);
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

	}*/
}
