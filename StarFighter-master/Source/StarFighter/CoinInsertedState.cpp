// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinInsertedState.h"
#include "OldSchoolSlotMachine.h"

// Sets default values
ACoinInsertedState::ACoinInsertedState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoinInsertedState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinInsertedState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinInsertedState::SetSlotMachine(AOldSchoolSlotMachine* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}
void ACoinInsertedState::InsertCoin()
{
	//Log the Insert Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You cannot insert another casino coin"));
}
void ACoinInsertedState::RejectCoin()
{
	//Log the Reject Coin string and set the state to "No Coin State"
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Casino coin returned"));
	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine->GetNoCoinState());
}
void ACoinInsertedState::PullLever()
{
	//Log the Pull Lever string and set the state to "Won Dollars State"
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You pulled the lever..."));
	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine->GetWonDollarsState());
}
void ACoinInsertedState::Payout()
{
	//Log the Payout string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No dollars dispensed"));
}
void ACoinInsertedState::RestockDollars() { /*Nothing*/ }
FString ACoinInsertedState::ToString()
{
	//Return the String of this state
	return "waiting for lever pull";
}