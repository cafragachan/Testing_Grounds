// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "Terrain/ActorPool.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() : Super()
{
	NavPool = CreateDefaultSubobject<UActorPool>("NavPool");
}

void AInfiniteTerrainGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	PopulateBoundsVolumePool();

}

void AInfiniteTerrainGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * NavMesh)
{
	NavPool->AddActorToPool(NavMesh);
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavMeshIterator) 
	{
		ANavMeshBoundsVolume* FoundNavMesh = *NavMeshIterator;
		AddToPool(FoundNavMesh);

		++NavMeshIterator;

		if (FoundNavMesh) UE_LOG(LogTemp, Warning, TEXT("navmeshfound: %s"), *FoundNavMesh->GetName());

	}
}
