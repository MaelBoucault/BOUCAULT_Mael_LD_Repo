#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForestExit.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UPointLightComponent;

/**
 * Sortie du niveau (pointe nord). Invisible et inactive au départ.
 * Le PNJ appelle Reveal() quand les 5 champignons sont livrés.
 */
UCLASS()
class AForestExit : public AActor
{
	GENERATED_BODY()

public:
	AForestExit();

	UFUNCTION(BlueprintCallable, Category = "Forest")
	void Reveal();

	UFUNCTION(BlueprintPure, Category = "Forest")
	bool IsRevealed() const { return bRevealed; }

	/** Événement Blueprint : fin de partie (écran de victoire, OpenLevel, etc.). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Forest")
	void OnPlayerEscaped();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forest")
	float LightIntensity = 15000.f;

	/** Grand rayon : la lumière doit être vue de loin, au-dessus du fog. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forest")
	float LightRadius = 3000.f;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPointLightComponent> Light;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bRevealed = false;
};
