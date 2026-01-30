#include "CoinItem.h"

ACoinItem::ACoinItem()
{
	PointValue = 50;
	ItemType = "Coin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Point %d"), PointValue));
		DestroyItem();
	}
}


