// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingComponent.h"


TArray<AActor*> UPatrollingComponent::GetTargetPoints() const
{
	return TargetPoints;
}
