// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinNumber, int MaxNumber)
{
	FVector Pos = GetActorLocation();

	int Num = FMath::RandRange(MinNumber, MaxNumber);

	for (int i = 0; i < Num; i++)
	{
		FVector Center = FMath::RandPointInBox(FBox(FVector(0, 1800, 0), FVector(3500, -1800, 0)));
		//DrawDebugSphere(GetWorld(), Center, 100, 20, FColor::Cyan, true);

		auto SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);

		if (ensure(SpawnedActor))
		{
			SpawnedActor->SetActorRelativeLocation(Center);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

}

