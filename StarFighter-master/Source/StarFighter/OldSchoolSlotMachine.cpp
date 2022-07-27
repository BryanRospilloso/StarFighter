// Fill out your copyright notice in the Description page of Project Settings.


#include "OldSchoolSlotMachine.h"
#include "NoDollarsState.h"
#include "NoCoinState.h"
#include "CoinInsertedState.h"
#include "WonDollarsState.h"

// Sets default values
AOldSchoolSlotMachine::AOldSchoolSlotMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOldSchoolSlotMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOldSchoolSlotMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOldSchoolSlotMachine::Initialize(int NumberOfDollars)
{
	//Spanw the No Dollars State and set this Slot Machine to it
	NoDollarsState = GetWorld()->SpawnActor<ANoDollarsState>(ANoDollarsState::StaticClass());
	NoDollarsState->SetSlotMachine(this);
	//Spanw the No Coin State and set this Slot Machine to it
	NoCoinState = GetWorld()->SpawnActor<ANoCoinState>(ANoCoinState::StaticClass());
	NoCoinState->SetSlotMachine(this);
	//Spanw the Coin Inserted State and set this Slot Machine to it
	CoinInsertedState = GetWorld()->SpawnActor<ACoinInsertedState>(ACoinInsertedState::StaticClass());
	CoinInsertedState->SetSlotMachine(this);
	//Spanw the Won Dollars State and set this Slot Machine to it
	WonDollarsState = GetWorld()->SpawnActor<AWonDollarsState>(AWonDollarsState::StaticClass());
	WonDollarsState->SetSlotMachine(this);
	//Set the amount of dollars
	Count = NumberOfDollars;
	//If its greater than 0, set the current State to No Coin State
	if (NumberOfDollars > 0) {
		State = NoCoinState;
	}
	else {
		State = NoDollarsState;
	}
}
void AOldSchoolSlotMachine::InsertCoin()
{
	//Execute the Insert Coin routine based on the current state
	State->InsertCoin();
}
void AOldSchoolSlotMachine::RejectCoin()
{
	//Execute the Reject Coin routine based on the current state
	State->RejectCoin();
}
void AOldSchoolSlotMachine::PullLever()
{
	//Execute the Pull Lever and Payout routine based on the current state
	State->PullLever();
	State->Payout();
}
void AOldSchoolSlotMachine::EmitDollars()
{
	//You won!
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Make it Rain!"));
	//If the Slot Machine still have some dollars, decrease them by 50
	if (Count != 0) {
		Count = Count - 50;
	}
}
int AOldSchoolSlotMachine::GetCount()
{
	//Returns the Dollars count
	return Count;
}
void AOldSchoolSlotMachine::RestockDollars(int myCount)
{
	//Add the passed count to the Dollars amount and log it
	Count += myCount;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("The Old School Slot Machine was just filled and new dollar count is : % i"), Count));
	//Then execute the Restock Dollars routine based on the current state
	State->RestockDollars();
}
void AOldSchoolSlotMachine::SetState(IState* myState)
{
	//Set the current state to the passed one
	State = myState;
}
IState* AOldSchoolSlotMachine::GetState()
{
	//Returns the Current State
	return State;
}
IState* AOldSchoolSlotMachine::GetNoDollarsState()
{
	//Returns the No Dollars State
	return NoDollarsState;
}
IState* AOldSchoolSlotMachine::GetNoCoinState()
{
	//Returns the No Coin State
	return NoCoinState;
}
IState* AOldSchoolSlotMachine::GetCoinInsertedState()
{
	//Returns the Coin Inserted State
	return CoinInsertedState;
}
IState* AOldSchoolSlotMachine::GetWonDollarsState()
{
	//Returns the Won Dollars State
	return WonDollarsState;
}
FString AOldSchoolSlotMachine::GetCurrentState()
{
	//Returns the 'Name' of current State
	return "Current Slot Machine State:" + State->ToString();
}