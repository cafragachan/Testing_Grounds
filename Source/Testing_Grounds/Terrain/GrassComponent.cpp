// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"
#include "Tile.h"


// Called when the game starts or when spawned
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

	PlaceGrassFoliage();
}

void UGrassComponent::PlaceGrassFoliage()
{
	for (int i = 0; i < GrassArrayNumber; ++i)
	{
		FTransform InstanceTransform = FTransform(ATile::RandomPositionInTile());
		AddInstance(InstanceTransform);
	}
}

