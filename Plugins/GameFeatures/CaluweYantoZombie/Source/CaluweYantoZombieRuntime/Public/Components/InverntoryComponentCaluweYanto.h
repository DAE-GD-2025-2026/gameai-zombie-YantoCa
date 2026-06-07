#pragma once
 
#include "CoreMinimal.h"
#include  "Components/ActorComponent.h"

#include "Common/InventoryComponent.h"

#include "InverntoryComponentCaluweYanto.generated.h"

class ABaseItem;
class UInventoryComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CALUWEYANTOZOMBIERUNTIME_API UInventoryComponentCaluweYanto : public UActorComponent
{
	GENERATED_BODY()
	// Wrapper
public:
	UInventoryComponentCaluweYanto();
	
	bool IsInventoryFull() const;
	bool TryTakingItem(ABaseItem& Item);
	const TArray<ABaseItem*>& GetInventory() const;
	float GetPickupRange() const; 

	bool UsingItem(const EItemType& UsingItemType);
	bool HasItemInInventory(const EItemType& UsingItemType);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	UInventoryComponent* InventoryComponent{}; // Orginal component wrapped around
	
	int ItemCount{};
};