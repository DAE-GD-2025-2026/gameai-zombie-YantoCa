#pragma once
 
#include "CoreMinimal.h"
#include  "Components/ActorComponent.h"

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
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	UInventoryComponent* InventoryComponent{}; // Orginal component wrapped around
	
	int ItemCount{};
};