// Copyright Max
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

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

	// ...
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp,Error,TEXT("%s Missing pressure plate"), *GetOwner()->GetName())
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	FString JoinedStr;
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	

	return TotalMass;
}

