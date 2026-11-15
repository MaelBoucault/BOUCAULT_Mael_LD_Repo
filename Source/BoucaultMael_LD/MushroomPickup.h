#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MushroomPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UPointLightComponent;

/**
 * Champignon à ramasser. Se ramasse en marchant dessus (overlap).
 * Émet une lueur verte pulsante = indice de guidage.
 * Règle pour le LD : HintRadius un peu inférieure à la distance de visibilité du fog.
 */
UCLASS()
class AMushroomPickup : public AActor
{
	GENERATED_BODY()

public:
	AMushroomPickup();

	virtual void Tick(float DeltaTime) override;

	/** Rayon de la lueur verte (indice visuel). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mushroom|Hint")
	float HintRadius = 800.f;

	/** Intensité moyenne de la lueur. M1 : forte, M5 : faible/en hauteur. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mushroom|Hint")
	float GlowIntensity = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mushroom|Hint")
	float PulseSpeed = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mushroom|Hint")
	FLinearColor GlowColor = FLinearColor(0.1f, 1.f, 0.2f);

	/** Événement Blueprint : jouer un son, des particules, etc. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Mushroom")
	void OnCollected();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPointLightComponent> Glow;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float TimeOffset = 0.f;
};
