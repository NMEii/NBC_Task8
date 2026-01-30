#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class TASK8_API IItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnOverlapItem(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) = 0;

	UFUNCTION()
	virtual void OnEndOverlapItem(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) = 0;
	virtual void ActivateItem(AActor* Activater) = 0;
	virtual FName GetItemType() const = 0;
	virtual void DestroyItem() = 0;
};
