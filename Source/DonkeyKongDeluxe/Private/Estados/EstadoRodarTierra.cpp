// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoRodarTierra.cpp

#include "Estados/EstadoRodarTierra.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoReposo.h"
#include "Estados/EstadoSalto.h" // Para transicion de emergencia

UEstadoRodarTierra::UEstadoRodarTierra()
{
	TiempoRollActual = 0.0f;
}

void UEstadoRodarTierra::OnEnter(ADKCPlayerCharacter* PersonajeReferencia)
{
	Super::OnEnter(PersonajeReferencia);

	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Roll de Tierra."));

	// Aplicar el Impulso (LaunchCharacter)
	const FVector DireccionMovimiento = Personaje->GetActorRightVector();
	const float FuerzaRoll = 1000.0f;

	Personaje->LaunchCharacter(DireccionMovimiento * FuerzaRoll, true, false);

	TiempoRollActual = 0.0f;
}

void UEstadoRodarTierra::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Roll de Tierra."));
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

	// 2. Transicion de emergencia: Si el personaje empieza a caer
	if (Personaje && Personaje->GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: Roll interrumpido (Caida). Yendo a Salto."));
		Personaje->CambiarEstado(NewObject<UEstadoSalto>(Personaje));
		return;
	}
}