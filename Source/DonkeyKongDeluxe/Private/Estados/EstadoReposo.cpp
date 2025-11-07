// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoReposo.cpp

#include "Estados/EstadoReposo.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoSalto.h"
#include "Estados/EstadoRodarTierra.h" // Incluido para la transicion

UEstadoReposo::UEstadoReposo()
{
}

void UEstadoReposo::OnEnter(ADKCPlayerCharacter* PersonajeReferencia)
{
	Super::OnEnter(PersonajeReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Reposo/Caminando"));
}

void UEstadoReposo::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Reposo/Caminando"));
}

void UEstadoReposo::TickState(float DeltaTime)
{
	// Transicion: Si el personaje empieza a caer 
	if (Personaje && Personaje->GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: De Reposo a Salto/Caida (inicio de caida)"));

		UEstadoSalto* NuevoEstado = NewObject<UEstadoSalto>(Personaje);
		Personaje->CambiarEstado(NuevoEstado);
	}
}

void UEstadoReposo::ManejarInputSalto()
{
	if (Personaje)
	{
		Personaje->Jump();

		// Transicion inmediata al estado de Salto/Caida
		UEstadoSalto* NuevoEstado = NewObject<UEstadoSalto>(Personaje);
		Personaje->CambiarEstado(NuevoEstado);
	}
}

void UEstadoReposo::ManejarInputRodar()
{
	// Solo permitimos rodar si el personaje esta en el suelo
	if (Personaje)
	{
		Personaje->EjecutarRodarAccion(); // Delega a la estrategia de DK/Diddy
	}
}