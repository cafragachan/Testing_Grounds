// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Public/Math/TransformNonVectorized.h"

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
	int Num = FMath::RandRange(MinNumber, MaxNumber);

	for (int i = 0; i < Num; i++)
	{
		FVector Location;
		FindEmptyLocation(Location, 250);
		PlaceActor(ActorToSpawn, Location);
	}
}

bool ATile::CanSpawnAtLocation(FVector Location_, float Radius)
{
	FHitResult HitResult;
	FVector WorldPos = GetTransform().TransformPosition(Location_);

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		WorldPos,
		WorldPos,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	FColor HitColor = bHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), WorldPos, 0, Radius, FQuat::Identity, HitColor, true, 50);

	return !bHit;
}

bool ATile::FindEmptyLocation(FVector& OUTTestLocation_, float Radius_)
{
	FVector BoxMin = FVector(0, 1800, 0);
	FVector BoxMax = FVector(3500, -1800, 0);
	FBox Box = FBox(BoxMin, BoxMax);
	const int MAX_TRIES = 20;

	for (int i = 0; i < MAX_TRIES; ++i)
	{
		FVector RandLocation = FMath::RandPointInBox(Box);
		if (CanSpawnAtLocation(RandLocation, Radius_))
		{
			OUTTestLocation_ = RandLocation;
			return true;
		}
	}
	return  false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn_, FVector Location_)
{
	auto SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn_);

	if (ensure(SpawnedActor))
	{
		SpawnedActor->SetActorRelativeLocation(Location_);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

