#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ForestGameMode.generated.h"

class UMushroomHUDWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMushroomCountChanged, int32, Collected, int32, Required);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllMushroomsCollected);

/**
 * Garde le compteur de champignons et crée le HUD.
 * À définir comme GameMode dans World Settings (ou en Project Settings).
 */
UCLASS()
class AForestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Nombre de champignons demandés par le PNJ. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Forest")
	int32 RequiredMushrooms = 5;

	UPROPERTY(BlueprintReadOnly, Category = "Forest")
	int32 CollectedMushrooms = 0;

	/** Widget Blueprint (enfant de MushroomHUDWidget) à afficher. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Forest")
	TSubclassOf<UMushroomHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintAssignable, Category = "Forest")
	FOnMushroomCountChanged OnMushroomCountChanged;

	UPROPERTY(BlueprintAssignable, Category = "Forest")
	FOnAllMushroomsCollected OnAllMushroomsCollected;

	UFUNCTION(BlueprintCallable, Category = "Forest")
	void AddMushroom();

	UFUNCTION(BlueprintPure, Category = "Forest")
	bool HasAllMushrooms() const { return CollectedMushrooms >= RequiredMushrooms; }

	UFUNCTION(BlueprintPure, Category = "Forest")
	UMushroomHUDWidget* GetHUD() const { return HUD; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMushroomHUDWidget> HUD;
};
