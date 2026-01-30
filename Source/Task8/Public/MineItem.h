#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class TASK8_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USphereComponent> ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float DamageValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionDelay;

	FTimerHandle ExplosionTimerHandle;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();
	
};
