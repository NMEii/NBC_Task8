#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MyGameInstance.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawingBox"));
	SpawningBox->SetupAttachment(Scene);

}

AActor* ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

void ASpawnVolume::ClearItems()
{
	for (AActor* Item : SpawnActors)
	{
		// 아이템이 이미 파괴되었거나(플레이어가 먹어서), 유효하지 않은 경우를 체크
		if (Item && IsValid(Item))
		{
			// 월드에서 액터를 제거합니다.
			Item->Destroy();
		}
	}

	// 배열을 비워서 다음 웨이브를 준비합니다.
	SpawnActors.Empty();
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();

	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return nullptr;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);

	return SpawnedActor;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);


		UDataTable* CurrentItemTable = ItemDataTable[MyGameInstance->CurrentLevelIndex];
		CurrentItemTable->GetAllRows(ContextString, AllRows);

		if (AllRows.IsEmpty()) return nullptr;

		float TotalChance = 0.0f;
		for (const FItemSpawnRow* Row : AllRows)
		{
			if (Row)
			{
				TotalChance += Row->Spawnchance;
			}
		}

		const float RandValue = FMath::FRandRange(0.0f, TotalChance);
		float AccumulateChance = 0.0f;

		for (FItemSpawnRow* Row : AllRows)
		{
			AccumulateChance += Row->Spawnchance;
			if (RandValue <= AccumulateChance)
			{
				return Row;
			}
		}
	}
	return nullptr;
}
