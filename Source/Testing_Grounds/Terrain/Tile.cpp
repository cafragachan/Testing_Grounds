// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Public/Math/TransformNonVectorized.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "ActorPool.h"
#include "Classes/AI/Navigation/NavigationSystem.h"

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

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!ensure(NavPool)) return;
	NavPool->ReturnActorToPool(NavMesh);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool* NavPool_)
{
	NavPool = NavPool_;
	NavMesh = NavPool->Checkout();

	if (!(NavMesh))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] : no Pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] : NavMesh %s"), *GetName(), *NavMesh->GetName());

	NavMesh->SetActorLocation(GetActorLocation() + FVector(2000, 0 , 0));
	GetWorld()->GetNavigationSystem()->Build();
}

TArray<FSpawnTransform> ATile::SetRandomSpawnTransform(FRandomSpawn RandomSpawn)
{
	TArray<FSpawnTransform> SpawnTransformArray;

	int Num = FMath::RandRange(RandomSpawn.MinNumber, RandomSpawn.MaxNumber);
	for (int i = 0; i < Num; i++)
	{
		FSpawnTransform SpawnTransform;

		if (FindEmptyLocation(SpawnTransform.Location, RandomSpawn.Radius))
		{
			SpawnTransform.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnTransform.Scale = FMath::RandRange(RandomSpawn.MinScale, RandomSpawn.MaxScale);
			SpawnTransformArray.Add(SpawnTransform);
		}
	}
	return SpawnTransformArray;
}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, FRandomSpawn RandomSpawn)
{
	TArray<FSpawnTransform> SpawnTransforms = SetRandomSpawnTransform(RandomSpawn);

	for(auto& SpawnTransform : SpawnTransforms)
	{
			PlaceActor(ActorToSpawn, SpawnTransform);
	}
}

void ATile::Test(FRandomSpawn RandomSettings)
{
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

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn_, FSpawnTransform SpawnTransform)
{
	auto SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn_);

	if (ensure(SpawnedActor))
	{
		SpawnedActor->SetActorRelativeLocation(SpawnTransform.Location);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		SpawnedActor->SetActorRelativeRotation(FRotator(0, SpawnTransform.Rotation, 0));
		SpawnedActor->SetActorRelativeScale3D(FVector(SpawnTransform.Scale));
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

