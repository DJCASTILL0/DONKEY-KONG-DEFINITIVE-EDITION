// RUTA: Source/DonkeyKongDeluxe/Private/Interactuables/LlantaRebote.cpp

#include "Interactuables/LlantaRebote.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Includes para la l?gica de Overlap
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoSalto.h" // Para forzar el estado de salto

ALlantaRebote::ALlantaRebote()
{
	PrimaryActorTick.bCanEverTick = false;
	FuerzaRebote = 1200.0f;


	MeshLlanta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshLlanta"));
	RootComponent = MeshLlanta;

	MeshLlanta->SetCollisionProfileName(TEXT("BlockAllDynamic"));


	ZonaRebote = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaRebote"));
	ZonaRebote->SetupAttachment(RootComponent); // Se adjunta al mesh

	ZonaRebote->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	ZonaRebote->SetBoxExtent(FVector(60.f, 60.f, 30.f));
	
	ZonaRebote->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));


	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshLlanta->SetStaticMesh(MeshFinder.Object);
		// Ajustamos la escala (el BoxComponent de arriba es relativo a esto)
		MeshLlanta->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.25f));
	}

	ZonaRebote->OnComponentBeginOverlap.AddDynamic(this, &ALlantaRebote::OnOverlapLlanta);
}

void ALlantaRebote::OnOverlapLlanta(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{

		if (Jugador->GetVelocity().Z < 0)
		{
		
			Jugador->LaunchCharacter(FVector(0.f, 0.f, FuerzaRebote), false, false);

		
			Jugador->CambiarEstado(NewObject<UEstadoSalto>(Jugador));
		}
	}
}