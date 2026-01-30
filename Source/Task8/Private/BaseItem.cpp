#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapItem);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnEndOverlapItem);
}


void ABaseItem::OnOverlapItem(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
		// 아이템 사용 (획득) 로직 호출
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnEndOverlapItem(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

}

void ABaseItem::ActivateItem(AActor* Activater)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!")));
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
}
