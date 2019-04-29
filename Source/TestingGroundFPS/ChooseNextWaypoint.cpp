// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "PatrolRoute.h" //it is in different folder!!
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"



EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)//NEED TO CHANGE BUILD.CS TO ATTACH AI , GAMEPLAYTASK MODULE!!
{
	
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	


	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);//!!!!

	auto AIController = OwnerComp.GetAIOwner();

	auto AIPawn = AIController->GetPawn();

	auto PatrolRoute = AIPawn->FindComponentByClass<UPatrolRoute>();

	if(!ensure(PatrolRoute)) {return  EBTNodeResult::Failed;}
	//	void GetPatrolPoints();
	auto CurrentWaypoint = PatrolRoute->GetPatrolPointByIndex(Index);
	if (!ensure(CurrentWaypoint)) { return  EBTNodeResult::Failed; }


	//	void SetNextWayPoints();
	BlackboardComp->SetValueAsObject(NextWayPoint.SelectedKeyName, CurrentWaypoint);

	//	void CycleIndex();

	int NextIndex = ++Index % (PatrolRoute->PatrolPoints.Num());

	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);







//	auto PatrollingGuard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner->GetPawn());

//	int32 PatrolPointsLength = PatrollingGuard->PatrolPoints.Num();

	

	


//	auto IndexKey = BlackboardComp->GetValueAsInt("NextWayPointIndex");//struct.........indexkey needs type.....



	return EBTNodeResult::Succeeded;//NECESSARY TO MOVE ON, MEANS END NODE IN BP
}
