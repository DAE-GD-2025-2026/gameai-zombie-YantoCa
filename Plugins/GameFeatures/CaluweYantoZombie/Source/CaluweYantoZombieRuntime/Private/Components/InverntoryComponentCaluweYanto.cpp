#include "Components/InverntoryComponentCaluweYanto.h"

UInventoryComponentCaluweYanto::UInventoryComponentCaluweYanto()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponentCaluweYanto::BeginPlay()
{
	Super::BeginPlay();
}

bool UInventoryComponentCaluweYanto::IsInventoryFull() const
{
	return StoredItems.Num() >= MaxSlots;
}

bool UInventoryComponentCaluweYanto::TryTakingItem(ABaseItem* Item)
{
	if (!Item || IsInventoryFull())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Try Pickup Item: Failed"));
		return false; // Nope we aint taking that
	}
	StoredItems.Add(Item);
	
	// "Deleting" the object and dragging it along
	AActor* ItemActor = Cast<AActor>(Item);
	if (ItemActor)
	{
		ItemActor->SetActorHiddenInGame(true);
		ItemActor->SetActorEnableCollision(false);
		
		ItemActor->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Try Pickup Item: Success"));
	 
	return true;
}
