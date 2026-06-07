#include "Components/InverntoryComponentCaluweYanto.h"

#include "Common/InventoryComponent.h"

UInventoryComponentCaluweYanto::UInventoryComponentCaluweYanto()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	if (GetOwner())
	{
		InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();
		if (!InventoryComponent)
		{
			GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Red, TEXT("Coudlnt wrap around original component"));
		}
	}
}

void UInventoryComponentCaluweYanto::BeginPlay()
{
	Super::BeginPlay();
}

bool UInventoryComponentCaluweYanto::IsInventoryFull() const
{
	return ItemCount >= InventoryComponent->GetInventoryCapacity();
}

bool UInventoryComponentCaluweYanto::TryTakingItem(ABaseItem& Item)
{
	if (!&Item || IsInventoryFull()) return false; // Nope we aint taking that
	if (InventoryComponent->GetInventory().Contains(&Item)) return false; // avoid duplicates
	
	int slotIdx{};
	while (!InventoryComponent->GrabItem(slotIdx, &Item)) // Seek available slot 
	{
		// no limit needed because we already checked if it was full or not
		++slotIdx;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Try Pickup Item: Success"));
	++ItemCount; // count increase
	return true; 
}


const TArray<ABaseItem*>&  UInventoryComponentCaluweYanto::GetInventory() const
{
	return InventoryComponent->GetInventory();
}
float  UInventoryComponentCaluweYanto::GetPickupRange() const
{
	return InventoryComponent->GetPickupRange();
}
bool UInventoryComponentCaluweYanto::UsingItem(const EItemType& UsingItemType)
{
	if (!InventoryComponent) return false;
	//if (InventoryComponent->GetInventory().Contains(&UsingItemType)) return false; // avoid duplicates
	
	const TArray<ABaseItem*>&  currentInventory = GetInventory();
	bool bItemWasUsed = false;
	
	for (int i = 0; i < currentInventory.Num(); i++)
	{
		ABaseItem* currentItem = currentInventory[i];
		if (currentItem == nullptr || !IsValid(currentItem)) continue;
		
		if (currentItem->GetItemType() == UsingItemType) // Is current item the same type i am searching?
		{
			InventoryComponent->UseItem(i);
			bItemWasUsed = true;
			
			if (currentItem->GetValue() <= 0)
			{
				InventoryComponent->RemoveItem(i);
				break; // Stop with looking you found it dumb dumb
			}
		}
	}
	
	return bItemWasUsed;	
}