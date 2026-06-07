#include "Tasks/BTTask_FleeCaluweYanto.h"
#include "Tasks/BTTask_LootItemCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h" 


UBTTask_FleeCaluweYanto::UBTTask_FleeCaluweYanto()
{
	bNotifyTick = false;
	NodeName = "Flee Away";
}

EBTNodeResult::Type UBTTask_FleeCaluweYanto::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) 
{
	AAIController* Controller = root.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = root.GetBlackboardComponent();
	
	if (!BlackboardComponent || !Controller) return EBTNodeResult::Failed; 
	
	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed; 
	
	AActor* Zombie = Cast<AActor>(BlackboardComponent->GetValueAsObject(NearestZombieKey.SelectedKeyName));
    if (!Zombie)
    {  
        return EBTNodeResult::Failed;
    }
	
	FVector FleeDirection = (Pawn->GetActorLocation() - Zombie->GetActorLocation()).GetSafeNormal();
 
	FVector DesiredFleePos = Pawn->GetActorLocation() + (FleeDirection * FleeStrength);   
	//DesiredFleePos.Z = 0;
	GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something! %s"), *DesiredFleePos.ToString()));
	GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something! %s"), *Pawn->GetActorLocation().ToString()));
	BlackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, DesiredFleePos);
    return EBTNodeResult::Succeeded;
}
