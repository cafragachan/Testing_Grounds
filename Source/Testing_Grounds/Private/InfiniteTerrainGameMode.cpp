// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

void AInfiniteTerrainGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	PopulateBoundsVolumePool();
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * NavMesh)
{
	UE_LOG(LogTemp, Warning, TEXT("NavMesh: %s"), *NavMesh->GetName())
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavMeshIterator) 
	{
		ANavMeshBoundsVolume* FoundNavMesh = *NavMeshIterator;
		AddToPool(FoundNavMesh);

		++NavMeshIterator;
	}
}
