// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	auto Controller = OwnerComp.GetAIOwner();
	auto Pawn = Controller->GetPawn();
	auto PatrolRouteComponent = Pawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Failed; }
	
	auto PatrolPoints = PatrolRouteComponent->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("%s has no patrol points!"), *(Pawn->GetName()));
		return EBTNodeResult::Failed;
	}

	BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	auto NewIndex = (++Index) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);

	return EBTNodeResult::Succeeded;
}
