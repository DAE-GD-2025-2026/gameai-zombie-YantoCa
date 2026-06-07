#include "Tasks/BTTask_HealCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Components/InverntoryComponentCaluweYanto.h"
#include "GameFramework/Pawn.h" 

UBTTask_HealCaluweYanto::UBTTask_HealCaluweYanto()
{
	NodeName = "Heal yourself"; 
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_HealCaluweYanto::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	// made inventory comp
	UInventoryComponentCaluweYanto* Inventory =  Controller->GetPawn()->FindComponentByClass<UInventoryComponentCaluweYanto>(); 
	
	if (!Controller || !BlackboardComp || !Inventory) return EBTNodeResult::Failed;

	// Uses Item
	bool usedSuccesfull = Inventory->UsingItem(EItemType::Medkit);
	
	// check inventory again 
	BlackboardComp->SetValueAsBool(HasHealing.SelectedKeyName, Inventory->HasItemInInventory(EItemType::Medkit));
	BlackboardComp->SetValueAsBool(NeedsHealingKeyName.SelectedKeyName, false); // has healed
	
	if (!usedSuccesfull) return EBTNodeResult::Failed; 
	return EBTNodeResult::Succeeded;
}
