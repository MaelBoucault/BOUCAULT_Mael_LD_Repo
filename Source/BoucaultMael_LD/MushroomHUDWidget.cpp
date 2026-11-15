#include "MushroomHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UMushroomHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DialogueText)
	{
		DialogueText->SetVisibility(ESlateVisibility::Hidden);
	}

	// Caché au lancement, affiché seulement à la sortie.
	if (WinPanel)
	{
		WinPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMushroomHUDWidget::ShowWinPanel()
{
	HideDialogue();

	if (WinPanel)
	{
		WinPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UMushroomHUDWidget::UpdateCounter(int32 Collected, int32 Required)
{
	if (CounterText)
	{
		CounterText->SetText(FText::Format(
			NSLOCTEXT("Forest", "Counter", "Champignons : {0}/{1}"),
			FText::AsNumber(Collected), FText::AsNumber(Required)));
	}
}

void UMushroomHUDWidget::ShowDialogue(const FText& Text, float Duration)
{
	if (!DialogueText)
	{
		return;
	}

	DialogueText->SetText(Text);
	DialogueText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(DialogueTimer);
		if (Duration > 0.f)
		{
			World->GetTimerManager().SetTimer(DialogueTimer, this, &UMushroomHUDWidget::HideDialogue, Duration, false);
		}
	}
}

void UMushroomHUDWidget::HideDialogue()
{
	if (DialogueText)
	{
		DialogueText->SetVisibility(ESlateVisibility::Hidden);
	}
}
