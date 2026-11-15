#include "ForestNPC.h"
#include "ForestExit.h"
#include "ForestGameMode.h"
#include "MushroomHUDWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AForestNPC::AForestNPC()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->InitCapsuleSize(40.f, 90.f);
	Capsule->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Décalage standard des mannequins UE : pieds au sol, face à l'axe X de l'acteur.
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	Mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	// Assigne le Skeletal Mesh (ex. SKM_Manny) dans les Details ou dans un Blueprint enfant.

	HouseLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("HouseLight"));
	HouseLight->SetupAttachment(RootComponent);
	HouseLight->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	HouseLight->SetLightColor(FLinearColor(1.f, 0.55f, 0.15f)); // orange chaud = chemin sûr
	HouseLight->SetIntensity(12000.f);
	HouseLight->SetAttenuationRadius(2500.f);

	InteractZone = CreateDefaultSubobject<USphereComponent>(TEXT("InteractZone"));
	InteractZone->InitSphereRadius(300.f);
	InteractZone->SetupAttachment(RootComponent);
	InteractZone->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	InteractZone->OnComponentBeginOverlap.AddDynamic(this, &AForestNPC::OnZoneBegin);
	InteractZone->OnComponentEndOverlap.AddDynamic(this, &AForestNPC::OnZoneEnd);
}

void AForestNPC::BeginPlay()
{
	Super::BeginPlay();

	if (IdleAnimation && Mesh)
	{
		Mesh->PlayAnimation(IdleAnimation, true);
	}
}

void AForestNPC::OnZoneBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || !Character->IsPlayerControlled())
	{
		return;
	}

	AForestGameMode* GM = Cast<AForestGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GM)
	{
		return;
	}

	UMushroomHUDWidget* HUD = GM->GetHUD();

	if (!GM->HasAllMushrooms())
	{
		if (HUD)
		{
			HUD->ShowDialogue(FText::Format(
				NSLOCTEXT("Forest", "NPCNeeds", "Ah, tu est perdu, la seul façon de sortir d'ici, c'est faire la teuf! Ramène moi des champignons et je t'invite"),
				FText::AsNumber(GM->RequiredMushrooms - GM->CollectedMushrooms)), 0.f);
		}
		return;
	}

	if (!bExitRevealed)
	{
		bExitRevealed = true;
		if (ExitActor)
		{
			ExitActor->Reveal();
		}
		OnExitRevealed();
	}

	if (HUD)
	{
		HUD->ShowDialogue(NSLOCTEXT("Forest", "NPCThanks", "Merci. Je t'ouvre ma Maison ! La biz! ♥."), DialogueDuration);
	}
}

void AForestNPC::OnZoneEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || !Character->IsPlayerControlled())
	{
		return;
	}

	if (AForestGameMode* GM = Cast<AForestGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (UMushroomHUDWidget* HUD = GM->GetHUD())
		{
			HUD->HideDialogue();
		}
	}
}
