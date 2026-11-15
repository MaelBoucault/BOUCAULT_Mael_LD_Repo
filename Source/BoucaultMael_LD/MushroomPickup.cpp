#include "MushroomPickup.h"
#include "ForestGameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AMushroomPickup::AMushroomPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->InitSphereRadius(80.f);
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Trigger;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Assigne un mesh (sphère/cône d'engine) dans le Blueprint ou sur l'instance.

	Glow = CreateDefaultSubobject<UPointLightComponent>(TEXT("Glow"));
	Glow->SetupAttachment(RootComponent);
	Glow->SetCastShadows(false);
	Glow->SetRelativeLocation(FVector(0.f, 0.f, 40.f));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMushroomPickup::OnOverlapBegin);
}

void AMushroomPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Glow->SetAttenuationRadius(HintRadius);
	Glow->SetIntensity(GlowIntensity);
	Glow->SetLightColor(GlowColor);
	TimeOffset = FMath::FRandRange(0.f, 6.28f); // chaque champignon pulse décalé
}

void AMushroomPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Pulse = 0.75f + 0.25f * FMath::Sin(GetWorld()->GetTimeSeconds() * PulseSpeed + TimeOffset);
	Glow->SetIntensity(GlowIntensity * Pulse);
}

void AMushroomPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || !Character->IsPlayerControlled())
	{
		return;
	}

	if (AForestGameMode* GM = Cast<AForestGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->AddMushroom();
	}

	OnCollected();
	Destroy();
}
