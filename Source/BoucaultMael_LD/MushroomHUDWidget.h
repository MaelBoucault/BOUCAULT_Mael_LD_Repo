#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MushroomHUDWidget.generated.h"

class UTextBlock;
class UWidget;

/**
 * HUD de base en C++. Crée un Widget Blueprint qui hérite de cette classe
 * et ajoute deux TextBlock nommés EXACTEMENT :
 *  - CounterText   (obligatoire)  : "Champignons : 0/5"
 *  - DialogueText  (optionnel)    : texte du PNJ / messages
 */
UCLASS()
class UMushroomHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Forest|HUD")
	void UpdateCounter(int32 Collected, int32 Required);

	/** Affiche un texte. Duration <= 0 : reste affiché jusqu'à HideDialogue. */
	UFUNCTION(BlueprintCallable, Category = "Forest|HUD")
	void ShowDialogue(const FText& Text, float Duration = 4.f);

	UFUNCTION(BlueprintCallable, Category = "Forest|HUD")
	void HideDialogue();

	/** Affiche le panneau de victoire (widget nommé WinPanel). */
	UFUNCTION(BlueprintCallable, Category = "Forest|HUD")
	void ShowWinPanel();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CounterText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DialogueText;

	/** Panneau "U Win !" : doit s'appeler EXACTEMENT WinPanel dans le Designer. */
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UWidget> WinPanel;

private:
	FTimerHandle DialogueTimer;
};
