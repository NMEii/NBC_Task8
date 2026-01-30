#include "MineItem.h"
#include "Components/SphereComponent.h"

AMineItem::AMineItem()
{
	DamageValue = 30.0f;
	ExplosionRange = 300.0f;
	ExplosionDelay = 2.0f;
	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRange);		// 폭발 범위 지정
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));	// collision preset
	ExplosionCollision->SetupAttachment(Scene);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Damaged %.f"), DamageValue));
	}
}

void AMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;

	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Damaged %.f"), DamageValue));
		}
	}

	DestroyItem();

}
