#include "Tasks/BTTask_LootItemCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h" 

#include "StudentPerceptorCaluweYanto.h"
#include "Items/BaseItem.h"

UBTTask_LootItemCaluweYanto::UBTTask_LootItemCaluweYanto()
{
	NodeName = TEXT("Looting Item on Blackboard");
}

EBTNodeResult::Type UBTTask_LootItemCaluweYanto::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	AAIController* Controller = root.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = root.GetBlackboardComponent();
	
	if (!BlackboardComponent || !Controller) return EBTNodeResult::Failed; 
	
	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	// Get item
	ABaseItem* Item = Cast<ABaseItem>(BlackboardComponent->GetValueAsObject(ItemKey.SelectedKeyName));
	if (Item == nullptr) return EBTNodeResult::Failed; // Not a succesfull cast

	// Get inventory methods
	UStudentPerceptorCaluweYanto* Perceptor = Pawn->FindComponentByClass<UStudentPerceptorCaluweYanto>();
	if (!Perceptor || !Perceptor->GetInventory()) return EBTNodeResult::Failed; // No perceptor or component we need
	
	UInventoryComponentCaluweYanto* Inventory = Perceptor->GetInventory();
	
	// Checks before putting it in
	if (Inventory->IsInventoryFull()) return EBTNodeResult::Failed; // Already full no use filling it up
	
	float DistanceBetweenItemAndPlayer = FVector::Dist(Pawn->GetActorLocation(), Item->GetActorLocation());
	if (DistanceBetweenItemAndPlayer <= Inventory->GetPickupRange()) // Is withing pickup range
	{
		// try taking it
		if (Inventory->TryTakingItem(*Item))
		{
			
			// TODO ADD A FUNCTION THAT MAKES ROOM FOR ITEM (Upgrade)
			
			// Go through booleans
			BlackboardComponent->SetValueAsBool(HasWeapon.SelectedKeyName, Inventory->HasItemInInventory(EItemType::Pistol) || Inventory->HasItemInInventory(EItemType::Shotgun));
			BlackboardComponent->SetValueAsBool(HasFood.SelectedKeyName, Inventory->HasItemInInventory(EItemType::Food));
			BlackboardComponent->SetValueAsBool(HasHealing.SelectedKeyName, Inventory->HasItemInInventory(EItemType::Medkit));
			
			BlackboardComponent->SetValueAsBool(ItemSeenKeySelector.SelectedKeyName, false);
			BlackboardComponent->SetValueAsObject(ItemKey.SelectedKeyName, nullptr);
			
			GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Green, 
			FString::Printf(TEXT("Picked up: %s"), *Item->GetName())); 		
			return EBTNodeResult::Succeeded;
		}
		
		GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Red,TEXT("Couldnt Take item"));
		return EBTNodeResult::Failed;
	}
	
	GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Red,TEXT("Out of bounds"));
	return EBTNodeResult::Failed;
}