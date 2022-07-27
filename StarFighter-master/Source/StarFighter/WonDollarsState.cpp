// Fill out your copyright notice in the Description page of Project Settings.


#include "WonDollarsState.h"
#include "OldSchoolSlotMachine.h"

// Sets default values
AWonDollarsState::AWonDollarsState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWonDollarsState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWonDollarsState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWonDollarsState::SetSlotMachine(AOldSchoolSlotMachine* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}
void AWonDollarsState::InsertCoin()
{
	//Log the Insert Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Please wait, machine is dispensing dollars"));
}
void AWonDollarsState::RejectCoin()
{
	//Log the Reject Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Chill, you already pulled the lever"));
}
void AWonDollarsState::PullLever()
{
	//Log the Pull Lever string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Do not pull lever twice!"));
}
void AWonDollarsState::Payout()
{
	//Payout time! Emit the dollars from the Slot Machine
	OldSchoolSlotMachine->EmitDollars();
	if (OldSchoolSlotMachine->GetCount() > 0)
	{
		//If the Slot Machine still have dollars, set its state to No Coin State
		OldSchoolSlotMachine->SetState(OldSchoolSlotMachine->GetNoCoinState());
	}
	else
	{
		//If the Slot Machine doesn't have any dollars left, log it and set its state to No Dollars State
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Machine is now out of cash"));
		OldSchoolSlotMachine->SetState(OldSchoolSlotMachine->GetNoDollarsState());
	}
}
void AWonDollarsState::RestockDollars() { /*Nothing*/ }
FString AWonDollarsState::ToString()
{
	//Return the String of this state
	return "dispensing cash";
}