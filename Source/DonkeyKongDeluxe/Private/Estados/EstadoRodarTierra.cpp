// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoRodarTierra.cpp

#include "Estados/EstadoRodarTierra.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoReposo.h"
#include "Estados/EstadoSalto.h" 

UEstadoRodarTierra::UEstadoRodarTierra()
{
	TiempoRollActual = 0.0f;
	FriccionSueloOriginal = 0.0f;
	FuerzaRoll = 1000.0f;
}

// (LA CORRECCIÓN) La firma C++ ahora coincide con el .h
void UEstadoRodarTierra::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{
	// (LA CORRECCIÓN) Pasamos ambos parámetros C++ a la función base
	Super::OnEnter(PersonajeReferencia, ActorReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Roll de Tierra."));
	if (!Personaje) return;

	if (Personaje->GetCharacterMovement())
	{
		FriccionSueloOriginal = Personaje->GetCharacterMovement()->GroundFriction;
		Personaje->GetCharacterMovement()->GroundFriction = 0.0f;
	}

	const FVector DireccionImpulso = Personaje->GetActorForwardVector();
	Personaje->LaunchCharacter(DireccionImpulso * FuerzaRoll, true, false);

	TiempoRollActual = 0.0f;
}

void UEstadoRodarTierra::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Roll de Tierra."));
	if (!Personaje) return;

	if (Personaje->GetCharacterMovement())
	{
		Personaje->GetCharacterMovement()->GroundFriction = FriccionSueloOriginal;
	}
}

void UEstadoRodarTierra::TickState(float DeltaTime)
{
	TiempoRollActual += DeltaTime;

	if (TiempoRollActual >= DuracionMaximaRoll)
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: Roll de Tierra terminado. Volviendo a Reposo."));
		Personaje->CambiarEstado(NewObject<UEstadoReposo>(Personaje));
		return;
	}

	if (Personaje && Personaje->GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: Roll interrumpido (Caida). Yendo a Salto."));
		Personaje->CambiarEstado(NewObject<UEstadoSalto>(Personaje));
		return;
	}
}

bool UEstadoRodarTierra::EstaAtacando() const
{
	return true;
}