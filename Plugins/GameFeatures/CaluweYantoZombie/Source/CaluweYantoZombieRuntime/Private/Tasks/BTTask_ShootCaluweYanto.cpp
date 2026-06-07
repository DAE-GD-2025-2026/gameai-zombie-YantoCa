#include "Tasks/BTTask_ShootCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Components/InverntoryComponentCaluweYanto.h"
#include "GameFramework/Pawn.h" 

UBTTask_ShootCaluweYanto::UBTTask_ShootCaluweYanto()
{
	NodeName = "Shoot The Nearest Zombie"; 
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_ShootCaluweYanto::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	// made inventory comp
	UInventoryComponentCaluweYanto* Inventory =  Controller->GetPawn()->FindComponentByClass<UInventoryComponentCaluweYanto>(); 
	
	if (!Controller || !BlackboardComp || !Inventory) return EBTNodeResult::Failed;

	// First use shotgun
	bool shotZombie = Inventory->UsingItem(EItemType::Shotgun);
	// if failed try Pistol
	if (!shotZombie) shotZombie = Inventory->UsingItem(EItemType::Pistol);
	
	// check inventory again if we have weapons or not. for isWeaponed BOol
	BlackboardComp->SetValueAsBool(HasWeapon.SelectedKeyName, Inventory->HasItemInInventory(EItemType::Shotgun) || Inventory->HasItemInInventory(EItemType::Pistol));
	
	if (!shotZombie) return EBTNodeResult::Failed; // nothing Fired
	
	return EBTNodeResult::Succeeded;
}
