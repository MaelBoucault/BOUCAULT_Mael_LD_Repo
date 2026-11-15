#include "SoundGuideTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "Engine/World.h"
#include "TimerManager.h"

ASoundGuideTrigger::ASoundGuideTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetBoxExtent(FVector(300.f, 300.f, 200.f));
	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Box;

	Box->OnComponentBeginOverlap.AddDynamic(this, &ASoundGuideTrigger::OnBoxBegin);
}

void ASoundGuideTrigger::OnBoxBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || !Character->IsPlayerControlled())
	{
		return;
	}

	if (bOnlyOnce && bTriggered)
	{
		return;
	}
	bTriggered = true;

	if (Delay > 0.f)
	{
		GetWorldTimerManager().SetTimer(DelayTimer, this, &ASoundGuideTrigger::PlayGuideSound, Delay, false);
	}
	else
	{
		PlayGuideSound();
	}
}

void ASoundGuideTrigger::PlayGuideSound()
{
	if (!Sound)
	{
		return;
	}

	const FVector WorldLocation = GetActorTransform().TransformPosition(SoundLocation);

	UGameplayStatics::PlaySoundAtLocation(this, Sound, WorldLocation, FRotator::ZeroRotator,
		Volume, 1.f, 0.f, Attenuation);
}
