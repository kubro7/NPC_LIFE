// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAIController.h"
#include "NpcCharacter.h"



ANpcAIController::ANpcAIController(FObjectInitializer const& ObjectInitializer)
{
}

void ANpcAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(ANpcCharacter* const npc = Cast<ANpcCharacter>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
