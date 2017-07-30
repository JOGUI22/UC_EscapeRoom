// Copyright Jordi Casadevall Franco 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.f, openAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (pressurePlate->IsOverlappingActor(actorThatOpens)) {
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if its time to close the door
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay) {
		CloseDoor();
	}
}

