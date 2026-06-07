#include "Tasks/BTTask_FindNextHouseCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Components/HouseTrackerComponentCaluweYanto.h"
#include "StudentPerceptorCaluweYanto.h"
#include "Village/House/House.h"

UBTTask_FindNextHouseCaluweYanto::UBTTask_FindNextHouseCaluweYanto()
{
	NodeName = TEXT("Finding Next House");
}

EBTNodeResult::Type UBTTask_FindNextHouseCaluweYanto::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	AAIController* Controller = root.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = root.GetBlackboardComponent();
	
	if (!BlackboardComponent || !Controller) return EBTNodeResult::Failed; 
	
	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	 
	FVector housePosition = BlackboardComponent->GetValueAsVector(NextHousePositionKey.SelectedKeyName);

	if (housePosition.IsZero())
	{
		GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Red,TEXT("No vector"));
		return EBTNodeResult::Failed;
	}
	
	GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Green,TEXT("Found Vector and placed in TargetPos"));
	BlackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, housePosition);
	
	return EBTNodeResult::Succeeded;	
}
