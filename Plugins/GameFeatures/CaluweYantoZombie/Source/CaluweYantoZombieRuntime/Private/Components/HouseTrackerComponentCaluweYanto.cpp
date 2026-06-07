#include "Components/HouseTrackerComponentCaluweYanto.h"
#include "Village/House/House.h"

UHouseTrackerComponentCaluweYanto::UHouseTrackerComponentCaluweYanto()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHouseTrackerComponentCaluweYanto::AddHouse(AHouse* House)
{
	if (House != nullptr && !IsVisited(*House))
	{
		Houses.AddUnique(House); // Only adds if its unique
		EnforceMaxLimit(Houses);
	}
}

bool UHouseTrackerComponentCaluweYanto::IsVisited(const AHouse& House) const
{
	return VisitedHouses.Contains(&House);
}
bool UHouseTrackerComponentCaluweYanto::ContainsHouse(const AHouse& House) const
{
	return Houses.Contains(&House);
}

bool UHouseTrackerComponentCaluweYanto::IsHousesEmpty() const
{
	return Houses.IsEmpty();
}

bool  UHouseTrackerComponentCaluweYanto::MarkAsVisited(const FVector& currentPos)
{
	AHouse* HouseToMark = nullptr;
	
	for (AHouse* House : Houses)
	{
		FVector Origin;
		FVector Extent;
		House->GetActorBounds(true, Origin, Extent);
		
		FBox  currentBox(Origin - Extent, Origin + Extent);
		
		if (currentBox.IsInside(currentPos))
		{
			HouseToMark = House;
			break;
		}
	}
	
	if (HouseToMark != nullptr)
	{
		VisitedHouses.AddUnique(HouseToMark);
		Houses.Remove(HouseToMark);
        
		EnforceMaxLimit(VisitedHouses);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("HouseTracker: House Visited"));
		return true;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("HouseTracker: Called but None Found"));
	return false;
}

void UHouseTrackerComponentCaluweYanto::EnforceMaxLimit(TArray<AHouse*>& houses)
{
	// FIFO, remove the first one that entered. and add the new one
	if (houses.Num() > MaxHouses)
	{
		houses.RemoveAt(0);
	}
}

FVector UHouseTrackerComponentCaluweYanto::GetNextUnvisitedHousePosition()
{
	if (!Houses.IsEmpty() && Houses[0] != nullptr)
	{
		AHouse* targetHouse = Houses[0];
		
		return targetHouse->GetActorLocation();
	}
	
	return FVector::ZeroVector; // Empty no houses left to visit
}
