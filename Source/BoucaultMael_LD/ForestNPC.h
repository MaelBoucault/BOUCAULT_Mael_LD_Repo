#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForestNPC.generated.h"

class UCapsuleComponent;
class USphereComponent;
class USkeletalMeshComponent;
class UAnimationAsset;
class UPointLightComponent;
class AForestExit;

/**
 * PNJ au centre (la maison = le hub). Réagit à la proximité du joueur :
 *  - moins de 5 champignons : refuse et affiche le compteur.
 *  - 5 champignons : révèle la sortie.
 */
UCLASS()
class AForestNPC : public AActor
{
	GENERATED_BODY()

public:
	AForestNPC();

	/** La sortie à révéler (assigne-la sur l'instance dans le niveau). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	TObjectPtr<AForestExit> ExitActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	float DialogueDuration = 5.f;

	/** Animation en boucle (ex. idle du mannequin). Optionnel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	TObjectPtr<UAnimationAsset> IdleAnimation;

	/** Événement Blueprint : animation, son, etc. */
	UFUNCTION(BlueprintImplementableEvent, Category = "NPC")
	void OnExitRevealed();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bExitRevealed = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	/** Lumière orange chaude : fenêtre de la maison, visible de loin. */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPointLightComponent> HouseLight;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> InteractZone;

	UFUNCTION()
	void OnZoneBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnZoneEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	

};
