#include "ForestExit.h"
#include "ForestGameMode.h"
#include "MushroomHUDWidget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AForestExit::AForestExit()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->InitSphereRadius(150.f);
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision); // activé par Reveal()
	RootComponent = Trigger;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetVisibility(false);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(RootComponent);
	Light->SetRelativeLocation(FVector(0.f, 0.f, 300.f)); // en hauteur : visible au-dessus du fog
	Light->SetLightColor(FLinearColor(1.f, 0.85f, 0.6f));
	Light->SetCastShadows(false);
	Light->SetVisibility(false);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AForestExit::OnOverlapBegin);
}

void AForestExit::Reveal()
{
	if (bRevealed)
	{
		return;
	}
	bRevealed = true;

	Mesh->SetVisibility(true);
	Light->SetAttenuationRadius(LightRadius);
	Light->SetIntensity(LightIntensity);
	Light->SetVisibility(true);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AForestExit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!bRevealed || !Character || !Character->IsPlayerControlled())
	{
		return;
	}

	if (AForestGameMode* GM = Cast<AForestGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (UMushroomHUDWidget* HUD = GM->GetHUD())
		{
			HUD->ShowWinPanel();
		}
	}

	OnPlayerEscaped();
}
