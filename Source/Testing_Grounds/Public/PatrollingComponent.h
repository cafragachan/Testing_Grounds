// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_GROUNDS_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Patrol")
	TArray<AActor*> TargetPoints;

public:

	TArray<AActor*> GetTargetPoints() const;
	
};
