#include "HealingItem.h"

AHealingItem::AHealingItem()
{
	HealAmount = 30.0f;
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Healed %.f"), HealAmount));
		DestroyItem();
	}
}
