#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class TASK8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

protected:

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TObjectPtr<UBoxComponent> SpawningBox;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem(TSubclassOf<AActor> ItemClass);


};
