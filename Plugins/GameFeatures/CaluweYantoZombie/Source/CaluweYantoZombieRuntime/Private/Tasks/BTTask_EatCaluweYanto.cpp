#include "Tasks/BTTask_EatCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Components/InverntoryComponentCaluweYanto.h"
#include "GameFramework/Pawn.h" 

UBTTask_EatCaluweYanto::UBTTask_EatCaluweYanto()
{
	NodeName = "Feed yourself"; 
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_EatCaluweYanto::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	// made inventory comp
	UInventoryComponentCaluweYanto* Inventory =  Controller->GetPawn()->FindComponentByClass<UInventoryComponentCaluweYanto>(); 
	
	if (!Controller || !BlackboardComp || !Inventory) return EBTNodeResult::Failed;

	// Uses item
	bool usedSuccesfull = Inventory->UsingItem(EItemType::Food);
	
	// check inventory again 
	BlackboardComp->SetValueAsBool(HasFood.SelectedKeyName, Inventory->HasItemInInventory(EItemType::Food));
	BlackboardComp->SetValueAsBool(NeedsFood.SelectedKeyName, false);
	
	if (!usedSuccesfull) return EBTNodeResult::Failed; 
	return EBTNodeResult::Succeeded;
}
