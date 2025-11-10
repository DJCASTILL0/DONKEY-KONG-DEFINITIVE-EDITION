// RUTA: Source/DonkeyKongDeluxe/Private/Consumibles/LetraKong.cpp

#include "Consumibles/LetraKong.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "Componentes/ComponenteInventario.h" 

ALetraKong::ALetraKong()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Colision de Esfera
	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	RootComponent = ColisionEsfera;

	// 2. Usamos el perfil de colision que sabemos que funciona:
	ColisionEsfera->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	// 3. Mesh Visual (Creamos el componente, pero no asignamos mesh)
	// (Tú asignarás el mesh K, O, N, o G manualmente en el Blueprint)
	MeshLetra = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshLetra"));
	MeshLetra->SetupAttachment(RootComponent);
	MeshLetra->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 4. Suscribir el callback de Overlap
	ColisionEsfera->OnComponentBeginOverlap.AddDynamic(this, &ALetraKong::OnOverlap);
}

// ... (Constructor y BeginPlay sin cambios) ...

void ALetraKong::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteInventario* Inventario = Jugador->GetComponenteInventario();
		if (Inventario)
		{
			// (LA CORRECCIÓN)
			// Llamamos a la función que añade 1 letra
			Inventario->AnadirLetraKONG();
			Destroy();
		}
	}
}