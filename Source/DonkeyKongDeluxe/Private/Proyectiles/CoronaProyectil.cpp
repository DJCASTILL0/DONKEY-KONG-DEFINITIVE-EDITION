// RUTA: Source/DonkeyKongDeluxe/Private/Proyectiles/CoronaProyectil.cpp

#include "Proyectiles/CoronaProyectil.h"

// Includes C++
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Componentes/ComponenteSalud.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "Enemigos/KingKRool.h" 
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


ACoronaProyectil::ACoronaProyectil()
{
	// Activamos el Tick C++
	PrimaryActorTick.bCanEverTick = true;

	// Variables C++ puras
	DistanciaMaximaRecorrido = 1000.f; // 1000 unidades (10 metros)
	bEstaRegresando = false;

	// (Heredado de AProyectilBase)
	// MovimientoProyectil->ProjectileGravityScale = 0.f;
}

void ACoronaProyectil::BeginPlay()
{
	Super::BeginPlay();

	// (NUEVO) Guardamos la ubicación inicial C++
	UbicacionInicial = GetActorLocation();

	// (NUEVO) Hacemos que la corona ignore al jefe C++ al que pertenece
	if (JefeKRool)
	{
		ColisionEsfera->IgnoreActorWhenMoving(JefeKRool, true);
	}
}

void ACoronaProyectil::IniciarBumeran(AKingKRool* Jefe)
{
	JefeKRool = Jefe;

	// (NUEVO) El movimiento C++ es relativo a la rotación del jefe
	if (JefeKRool)
	{
		// Usamos la velocidad C++ del componente padre
		MovimientoProyectil->Velocity = JefeKRool->GetActorForwardVector() * MovimientoProyectil->InitialSpeed;
	}
}

// (LÓGICA C++ BASADA EN TU CÓDIGO)
void ACoronaProyectil::Tick(float DeltaTime)
{
	Super::Super::Tick(DeltaTime); // Llamamos al Tick del abuelo (AActor)

	// Si la corona no está volviendo...
	if (!bEstaRegresando)
	{
		// ...calculamos la distancia C++ que ha recorrido.
		float DistanciaRecorrida = FVector::Dist(UbicacionInicial, GetActorLocation());

		// Si ha superado la distancia máxima C++...
		if (DistanciaRecorrida >= DistanciaMaximaRecorrido)
		{
			// ...activamos el modo de retorno C++ e invertimos su velocidad C++.
			bEstaRegresando = true;
			MovimientoProyectil->Velocity *= -1.f;
		}
	}
	else // Si ya está volviendo...
	{
		// ...calculamos la distancia C++ al punto de origen.
		float DistanciaAlInicio = FVector::Dist(UbicacionInicial, GetActorLocation());

		// Si está muy cerca del origen C++, la destruimos.
		if (DistanciaAlInicio < 100.f)
		{
			Destroy();
		}
	}
}

void ACoronaProyectil::OnHitProyectil(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 1. ¿Chocamos con el Jugador C++?
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteSalud* SaludJugador = Jugador->GetComponenteSalud();
		if (SaludJugador) { SaludJugador->RecibirDanio(Dano); }
		Destroy();
		return;
	}

	// 2. ¿Chocamos con K. Rool (nuestro dueño)?
	AKingKRool* Jefe = Cast<AKingKRool>(OtherActor);
	if (Jefe && bEstaRegresando)
	{
		UE_LOG(LogTemp, Warning, TEXT("Corona C++: ¡Jefe atrapó la corona!"));
		Destroy();
		return;
	}

	// 3. (NUEVO) Si chocamos con cualquier otra cosa (pared/suelo)
	if (!bEstaRegresando)
	{
		bEstaRegresando = true;
		MovimientoProyectil->Velocity *= -1.f;
		UE_LOG(LogTemp, Warning, TEXT("Corona C++: ¡Rebotando en pared!"));
	}
}