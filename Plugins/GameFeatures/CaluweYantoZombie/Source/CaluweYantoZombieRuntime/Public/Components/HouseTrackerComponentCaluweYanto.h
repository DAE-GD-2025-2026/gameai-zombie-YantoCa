#pragma once
 
#include "CoreMinimal.h"
#include  "Components/ActorComponent.h"

#include "HouseTrackerComponentCaluweYanto.generated.h"

class AHouse;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CALUWEYANTOZOMBIERUNTIME_API UHouseTrackerComponentCaluweYanto : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UHouseTrackerComponentCaluweYanto();
	
	bool ContainsHouse(const AHouse& House) const;
	void AddHouse(AHouse* House);
	bool IsVisited(const AHouse& House) const;
	
	bool IsHousesEmpty() const;
	
	bool MarkAsVisited(const FVector& currentPosition);
	FVector GetNextUnvisitedHousePosition() ;	
private: 
	UPROPERTY()
	TArray<AHouse*> Houses;
	UPROPERTY()
	TArray<AHouse*> VisitedHouses{};
	
	const int32 MaxHouses = 10;
	void EnforceMaxLimit(TArray<AHouse*>& houses);
};