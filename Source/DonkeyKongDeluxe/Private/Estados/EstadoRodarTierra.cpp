// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoRodarTierra.cpp

#include "Estados/EstadoRodarTierra.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoReposo.h"
#include "Estados/EstadoSalto.h" 

UEstadoRodarTierra::UEstadoRodarTierra()
{
	TiempoRollActual = 0.0f;
	FriccionSueloOriginal = 0.0f; // Valor por defecto
	FuerzaRoll = 1000.0f; // Fuerza del impulso
}

void UEstadoRodarTierra::OnEnter(ADKCPlayerCharacter* PersonajeReferencia)
{
	Super::OnEnter(PersonajeReferencia);

	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Roll de Tierra."));

	if (!Personaje) return;

	// 1. (MEJORA DE SENSACION) Guardar y Desactivar Friccion del Suelo
	if (Personaje->GetCharacterMovement())
	{
		FriccionSueloOriginal = Personaje->GetCharacterMovement()->GroundFriction;
		// Sin friccion, el impulso durara mas y sera mas suave
		Personaje->GetCharacterMovement()->GroundFriction = 0.0f;
	}

	// 2. (LA CORRECCION) Aplicar el Impulso usando el Vector FORWARD
	// El Actor's Forward Vector (GetActorForwardVector) es el Eje X del Actor.
	// Gracias a "bOrientRotationToMovement", el Eje X del Actor se alinea 
	// con la direccion de movimiento (el Eje Y del Mundo).
	const FVector DireccionImpulso = Personaje->GetActorForwardVector();

	// Aplicamos el impulso (LaunchCharacter)
	Personaje->LaunchCharacter(DireccionImpulso * FuerzaRoll, true, false);

	TiempoRollActual = 0.0f;
}

void UEstadoRodarTierra::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Roll de Tierra."));

	if (!Personaje) return;

	// 1. (MEJORA DE SENSACION) Restaurar Friccion del Suelo
	if (Personaje->GetCharacterMovement())
	{
		Personaje->GetCharacterMovement()->GroundFriction = FriccionSueloOriginal;
	}
}

void UEstadoRodarTierra::TickState(float DeltaTime)
{
	TiempoRollActual += DeltaTime;

	// 1. Comprobar si el tiempo ha terminado
	if (TiempoRollActual >= DuracionMaximaRoll)
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: Roll de Tierra terminado. Volviendo a Reposo."));
		Personaje->CambiarEstado(NewObject<UEstadoReposo>(Personaje));
		return;
	}

	// 2. Transicion de emergencia (Caida)
	if (Personaje && Personaje->GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: Roll interrumpido (Caida). Yendo a Salto."));
		Personaje->CambiarEstado(NewObject<UEstadoSalto>(Personaje));
		return;
	}
}