#pragma once
 
#include "CoreMinimal.h"
#include  "Components/ActorComponent.h"

#include "Components/InverntoryComponentCaluweYanto.generated.h"

class ABaseItem;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CALUWEYANTOZOMBIERUNTIME_API UInventoryComponentCaluweYanto : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UInventoryComponentCaluweYanto();
	
	bool IsInventoryFull() const;
	bool TryTakingItem(ABaseItem* Item);
	const TArray<ABaseItem*>& GetInventory() const { return StoredItems;	};
	float GetPickupRange() const { return PickupRange;};
	
protected:
	virtual void BeginPlay() override;
	
private:
	const int32 MaxSlots{ 10 };
	const float PickupRange{ 150.f };
	
	UPROPERTY()
	TArray<ABaseItem*> StoredItems;
};