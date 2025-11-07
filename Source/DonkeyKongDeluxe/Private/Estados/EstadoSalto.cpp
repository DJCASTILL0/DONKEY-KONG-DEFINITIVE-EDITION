// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoSalto.cpp

#include "Estados/EstadoSalto.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoReposo.h" 

UEstadoSalto::UEstadoSalto()
{
}

void UEstadoSalto::OnEnter(ADKCPlayerCharacter* PersonajeReferencia)
{
	Super::OnEnter(PersonajeReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Salto/Caida"));
}

void UEstadoSalto::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Salto/Caida"));
}

void UEstadoSalto::TickState(float DeltaTime)
{
	// Transicion: Si el personaje toca el suelo
	if (Personaje && !Personaje->GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("TRANSICION: De Salto/Caida a Reposo (aterrizaje)"));
		Personaje->CambiarEstado(NewObject<UEstadoReposo>(Personaje));
	}
}
// Las funciones ManejarInputSalto y ManejarInputRodar estan vacias, bloqueando acciones.