// RUTA: Source/DonkeyKongDeluxe/Private/Estados/PlayerBaseState.cpp

#include "Estados/PlayerBaseState.h"

void UPlayerBaseState::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{
	Personaje = PersonajeReferencia;
}
void UPlayerBaseState::OnExit() {}
void UPlayerBaseState::TickState(float DeltaTime) {}
void UPlayerBaseState::ManejarInputSalto() {}
void UPlayerBaseState::ManejarInputRodar() {}
bool UPlayerBaseState::EstaAtacando() const { return false; }
void UPlayerBaseState::ManejarInputMoverArriba(float Valor) {}

// (NUEVO) Implementación C++ base (vacía)
void UPlayerBaseState::ManejarInputMoverDerecha(float Valor)
{
	// La mayoría de los estados ignoran este input
}