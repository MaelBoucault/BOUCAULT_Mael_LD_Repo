#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundGuideTrigger.generated.h"

class UBoxComponent;
class USoundBase;
class USoundAttenuation;

/**
 * Quand le joueur entre dans la box, un son est joué à un AUTRE endroit
 * (spatialisé) pour attirer son attention dans cette direction.
 * Dans l'éditeur, SoundLocation apparaît comme un petit losange déplaçable.
 */
UCLASS()
class ASoundGuideTrigger : public AActor
{
	GENERATED_BODY()

public:
	ASoundGuideTrigger();

	/** Le son à jouer (cloche, craquement, murmure, hululement...). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	TObjectPtr<USoundBase> Sound;

	/** Où le son est émis, relatif à cet acteur (gizmo dans le viewport). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide", meta = (MakeEditWidget = true))
	FVector SoundLocation = FVector(1500.f, 0.f, 0.f);

	/** Optionnel : atténuation (portée audible). Sinon celle du Sound est utilisée. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	TObjectPtr<USoundAttenuation> Attenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	float Volume = 1.f;

	/** Délai avant de jouer le son (s). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	float Delay = 0.5f;

	/** Ne joue qu'une fois (sinon à chaque entrée dans la box). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	bool bOnlyOnce = true;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UFUNCTION()
	void OnBoxBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlayGuideSound();

private:
	bool bTriggered = false;
	FTimerHandle DelayTimer;
};
