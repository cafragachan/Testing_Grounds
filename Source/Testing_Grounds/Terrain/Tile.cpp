// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Public/Math/TransformNonVectorized.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

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

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinNumber, int MaxNumber, float Radius_, float MinScale, float MaxScale)
{
	int Num = FMath::RandRange(MinNumber, MaxNumber);

	for (int i = 0; i < Num; i++)
	{
		FVector Location;
		if (FindEmptyLocation(Location, Radius_))
		{
			float Rotation = FMath::RandRange(-180.f, 180.f);
			float RandScale = FMath::RandRange(MinScale, MaxScale);
			PlaceActor(ActorToSpawn, Location, Rotation, RandScale);
		}
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

	//DrawDebugCapsule(GetWorld(), WorldPos, 0, Radius, FQuat::Identity, HitColor, true, 50);

	return !bHit;
}

bool ATile::FindEmptyLocation(FVector& OUTTestLocation_, float Radius_)
{
	const int MAX_TRIES = 20;

	for (int i = 0; i < MAX_TRIES; ++i)
	{
		FVector RandLocation = RandomPositionInTile();
		if (CanSpawnAtLocation(RandLocation, Radius_))
		{
			OUTTestLocation_ = RandLocation;
			return true;
		}
	}
	return  false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn_, FVector Location_, float Rotation_, float Scale_)
{
	auto SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn_);

	if (ensure(SpawnedActor))
	{
		SpawnedActor->SetActorRelativeLocation(Location_);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		SpawnedActor->SetActorRelativeRotation(FRotator(0, Rotation_, 0));
		SpawnedActor->SetActorRelativeScale3D(FVector(Scale_, Scale_, Scale_));
	}
}


FVector ATile::RandomPositionInTile()
{
	FVector BoxMin = FVector(0, 2000, 0);
	FVector BoxMax = FVector(4000, -2000, 0);
	FBox Box = FBox(BoxMin, BoxMax);
	FVector RandLocation = FMath::RandPointInBox(Box);

	return RandLocation;
}

