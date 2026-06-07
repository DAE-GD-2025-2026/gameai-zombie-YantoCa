#pragma once

#include "CoreMinimal.h"
#include  "Components/ActorComponent.h"

#include "ZombieTrackerComponentCaluweYanto.generated.h"

class ABaseZombie;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CALUWEYANTOZOMBIERUNTIME_API UZombieTrackerComponentCaluweYanto : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UZombieTrackerComponentCaluweYanto();
	
	void AddZombie(ABaseZombie* Zombie);
	bool IsInDanger(const FVector& PlayerLocation) const;
	ABaseZombie* GetNearestZombie() const { return NeartestZombieZombie; };

	void UpdateNearestZombies(const FVector& PlayerLocation);
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TArray<ABaseZombie*> Zombies{};
	
	UPROPERTY()
	ABaseZombie* NeartestZombieZombie;
	
	const float CautionRange{1000.f};
	const float DangerRange{500.f};
};
