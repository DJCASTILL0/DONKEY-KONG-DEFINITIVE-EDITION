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

	// 1. (NUEVO) El Mesh S?LIDO (Ra?z)
	MeshLlanta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshLlanta"));
	RootComponent = MeshLlanta;
	// Configuramos el mesh para ser S?LIDO y bloquear al jugador
	MeshLlanta->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// 2. (NUEVO) La Zona de Rebote (Trigger)
	ZonaRebote = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaRebote"));
	ZonaRebote->SetupAttachment(RootComponent); // Se adjunta al mesh
	// Hacemos la caja un poco m?s ancha y alta que el mesh
	ZonaRebote->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	ZonaRebote->SetBoxExtent(FVector(60.f, 60.f, 30.f));
	// Usamos el perfil que S? funciona
	ZonaRebote->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	// 3. (C++ PURO) Cargar el Mesh (Cilindro)
	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshLlanta->SetStaticMesh(MeshFinder.Object);
		// Ajustamos la escala (el BoxComponent de arriba es relativo a esto)
		MeshLlanta->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.25f));
	}

	// 4. Suscribimos el Overlap (SOLO a la ZonaRebote)
	ZonaRebote->OnComponentBeginOverlap.AddDynamic(this, &ALlantaRebote::OnOverlapLlanta);
}

void ALlantaRebote::OnOverlapLlanta(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 1. ?Es el Jugador?
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		// 2. ?Est? cayendo sobre nosotros (pisot?n)?
		if (Jugador->GetVelocity().Z < 0)
		{
			// ?Rebote!
			Jugador->LaunchCharacter(FVector(0.f, 0.f, FuerzaRebote), false, false);

			// Forzamos al jugador al estado de salto
			Jugador->CambiarEstado(NewObject<UEstadoSalto>(Jugador));
		}
	}
}