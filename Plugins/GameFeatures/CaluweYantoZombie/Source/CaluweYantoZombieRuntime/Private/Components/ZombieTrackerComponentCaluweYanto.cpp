#include "Components/ZombieTrackerComponentCaluweYanto.h"
#include "Zombies/BaseZombie.h"

UZombieTrackerComponentCaluweYanto::UZombieTrackerComponentCaluweYanto()
{
	PrimaryComponentTick.bCanEverTick = false;
	NeartestZombieZombie = nullptr;
}
void UZombieTrackerComponentCaluweYanto::BeginPlay()
{
	Super::BeginPlay();
}
void UZombieTrackerComponentCaluweYanto::AddZombie(ABaseZombie* Zombie)
{
	if (Zombie != nullptr)
	{
		Zombies.AddUnique(Zombie);

	}
}

bool UZombieTrackerComponentCaluweYanto::IsInDanger(const FVector& PlayerLocation) const
{
	if (NeartestZombieZombie == nullptr) return false;
	
	float DistanceBetweenPlayerAndZombie = FVector::Dist(GetNearestZombie()->GetActorLocation(), PlayerLocation);
	return DistanceBetweenPlayerAndZombie < DangerRange;
}

void UZombieTrackerComponentCaluweYanto::UpdateNearestZombies(const FVector& PlayerLocation)
{
	NeartestZombieZombie = nullptr;
	float SmallestDistance{CautionRange};
	
	for (int32 i = Zombies.Num() - 1; i >= 0; --i)
	{
		ABaseZombie* Zombie = Zombies[i];
        
		if (Zombie == nullptr || !IsValid(Zombie))
		{
			Zombies.RemoveAt(i);
			continue;
		}

		float DistanceBetweenPlayerAndZombie = FVector::Dist(Zombie->GetActorLocation(), PlayerLocation);
        
		if (DistanceBetweenPlayerAndZombie > CautionRange) 
		{
			Zombies.RemoveAt(i);
			continue;
		}
		if (DistanceBetweenPlayerAndZombie < SmallestDistance)
		{
			SmallestDistance = DistanceBetweenPlayerAndZombie;
			NeartestZombieZombie = Zombie;
		}
	}
}


