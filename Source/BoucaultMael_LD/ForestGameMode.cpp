#include "ForestGameMode.h"
#include "MushroomHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void AForestGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			HUD = CreateWidget<UMushroomHUDWidget>(PC, HUDWidgetClass);
			if (HUD)
			{
				HUD->AddToViewport();
				HUD->UpdateCounter(CollectedMushrooms, RequiredMushrooms);
			}
		}
	}
}

void AForestGameMode::AddMushroom()
{
	CollectedMushrooms = FMath::Min(CollectedMushrooms + 1, RequiredMushrooms);

	if (HUD)
	{
		HUD->UpdateCounter(CollectedMushrooms, RequiredMushrooms);
	}

	OnMushroomCountChanged.Broadcast(CollectedMushrooms, RequiredMushrooms);

	if (HasAllMushrooms())
	{
		OnAllMushroomsCollected.Broadcast();
		if (HUD)
		{
			HUD->ShowDialogue(NSLOCTEXT("Forest", "AllCollected", "Tu les as tous. Retourne voir le vieil homme."), 5.f);
		}
	}
}
