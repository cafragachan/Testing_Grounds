// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPool::Checkout()
{
	if (NavMeshesPool.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No NavMeshes in Checkout"));
		return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("Checking out: %s"), *GetName());

	return NavMeshesPool.Pop();
}

void UActorPool::ReturnActorToPool(AActor * ActorToReturn)
{
	if (!(ActorToReturn))
	{
		UE_LOG(LogTemp, Warning, TEXT("no NavMesh in Return"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Return: %s"), *ActorToReturn->GetName());
	NavMeshesPool.Add(ActorToReturn);

}

void UActorPool::AddActorToPool(AActor * ActorToAdd)
{
	if (!(ActorToAdd))
	{
		UE_LOG(LogTemp, Warning, TEXT("no NavMesh in Add"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Add: %s"), *ActorToAdd->GetName());
	NavMeshesPool.Add(ActorToAdd);

}
